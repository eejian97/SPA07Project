#include "CFG.h"
#include <map>
#include <queue>
#include <stack>

CFG::CFG() {}

CFG::CFG(Table procStmtTable, Table nextTable, Table modifiesTable,
         Table usesTable, Table whileIfTable, Table whileParentTable,
         Table assignTable, int stmtCount)
    : procStmtTable(procStmtTable), whileIfTable(whileIfTable),
      whileParentTable(whileParentTable), modifiesTable(modifiesTable),
      usesTable(usesTable), assignTable(assignTable) {
  // Populate UsesAssignTable and ModifiesAssignTable
  assignTable.setHeader({"s"});
  usesTable.setHeader({"s", "v"});
  modifiesTable.setHeader({"s", "v"});
  usesAssignTable = usesTable;
  modifiesAssignTable = modifiesTable;
  usesAssignTable.mergeWith(assignTable);
  modifiesAssignTable.mergeWith(assignTable);

  // Populate initialGraph from nextTable (1-based indexing)
  initialGraph.resize(stmtCount + 1);
  for (auto data : nextTable.getData()) {
    int u = std::stoi(data[0]);
    int v = std::stoi(data[1]);
    initialGraph[u].emplace_back(v);
  }
  // Populate inDegree
  inDegree.resize(stmtCount + 1);
  for (int i = 1; i < initialGraph.size(); ++i) {
    for (auto j : initialGraph[i]) {
      inDegree[j]++;
    }
  }
  // Populate initial to compressed map
  for (auto data : procStmtTable.getData()) {
    int start = std::stoi(data[1]);
    numCompressedNodes++;
    // Procedure only has one statement
    if (initialGraph[start].empty()) {
      initialToCompressed[start] = numCompressedNodes;
    } else {
      populateInitialToCompressed(start, whileIfTable, inDegree);
    }
  }
  // Populate forward and reverse CompressedGraph
  populateCompressedToInitial();
  forwardCompressedGraph.resize(numCompressedNodes + 1);
  reverseCompressedGraph.resize(numCompressedNodes + 1);
  populateCompressedGraph(procStmtTable);
}

// Populate map from initial to compressed nodes
void CFG::populateInitialToCompressed(int start, Table whileIfTable,
                                      std::vector<int> inDegree) {
  // Iterative DFS to populate initialToCompressed
  std::vector<bool> visited(initialGraph.size() + 1, false);
  std::stack<int> stack;
  stack.push(start);
  initialToCompressed[start] = numCompressedNodes;
  while (!stack.empty()) {
    int u = stack.top();
    stack.pop();
    if (!visited[u]) {
      visited[u] = true;
    }
    for (auto v : initialGraph[u]) {
      if (!visited[v]) {
        stack.push(v);
        if (whileIfTable.contains({std::to_string(v)})) {
          // Child is while or if statement
          numCompressedNodes++;
          initialToCompressed[v] = numCompressedNodes;
        } else if (inDegree[v] > 1) {
          // Child has in degree > 1
          numCompressedNodes++;
          initialToCompressed[v] = numCompressedNodes;
        } else {
          // Parent is while or if statement
          if (whileIfTable.contains({std::to_string(u)})) {
            numCompressedNodes++;
            initialToCompressed[v] = numCompressedNodes;
          } else {
            initialToCompressed[v] = initialToCompressed[u];
          }
        }
      }
    }
  }
}

// Populate map from compressed to initial nodes
void CFG::populateCompressedToInitial() {
  for (auto i : initialToCompressed) {
    compressedToInitial[i.second].emplace_back(i.first);
  }
}

// Populate map from forward and reverse CFG
void CFG::populateCompressedGraph(Table procStmtTable) {
  // Traverse the initialGraph and populate forward and reverse CompressedGraph
  // using initialToCompressed
  std::vector<bool> visited(initialGraph.size() + 1, false);
  std::queue<int> queue;
  // Mark start of each procedure as visited and push into queue for traversal
  for (auto data : procStmtTable.getData()) {
    int start = std::stoi(data[1]);
    queue.push(start);
    visited[start] = true;
  }
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (auto v : initialGraph[u]) {
      if (!visited[v]) {
        queue.push(v);
        visited[v] = true;
      }
      if (initialToCompressed[v] != initialToCompressed[u]) {
        forwardCompressedGraph[initialToCompressed[u]].emplace_back(
            initialToCompressed[v]);
        reverseCompressedGraph[initialToCompressed[v]].emplace_back(
            initialToCompressed[u]);
      }
    }
  }
}

// Algorithm for Next*(constant, synonym)
std::deque<int> CFG::getNextTForward(int start, int end = -1) {
  // Use cached results if exists
  if (nextTForwardCache.count(start)) {
    return nextTForwardCache.at(start);
  }
  std::deque<int> result;
  std::vector<std::vector<int>> compressedCFG = forwardCompressedGraph;
  bool reachedEnd = false;
  // initialize visited array
  std::vector<bool> visited(initialToCompressed.size() + 1, false);
  visited[0] = true; // no stmt line 0
  // adding all elements in start node
  int startNode = initialToCompressed.at(start);
  std::vector<int> linesInNode = compressedToInitial.at(startNode);
  int index = start - linesInNode[0] + 1;
  for (int i = index; i < linesInNode.size(); i++) {
    result.emplace_back(linesInNode[i]);
    visited[linesInNode[i]] = true;
    if (linesInNode[i] == end) {
      reachedEnd = true;
    }
  }
  std::queue<int> q;
  q.push(startNode);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    for (int i : compressedCFG[curr]) {
      if (!visited[compressedToInitial.at(i)[0]]) {
        for (int j : compressedToInitial.at(
                 i)) { // adding all elements within current node
          if (!visited[j]) {
            visited[j] = true;
            result.emplace_back(j);
            if (j == end) { // for nextT with 2 constants
              reachedEnd = true;
              break;
            }
          }
        }
        q.push(i);
      }
    }
  }
  // for nextT with two constants that did not reach end line
  if ((end > 0) && (!reachedEnd)) {
    // return empty vector if end not reachable from start
    return std::deque<int>{};
  }
  auto cacheRes = nextTForwardCache.emplace(start, std::move(result));
  return cacheRes.first->second;
}

// Algorithm for Next*(synonym, constant)
std::deque<int> CFG::getNextTReverse(int start) {
  // Use cached results if exists
  if (nextTReverseCache.count(start)) {
    return nextTReverseCache.at(start);
  }
  std::deque<int> result;
  std::vector<std::vector<int>> compressedCFG = reverseCompressedGraph;
  std::vector<bool> visited(initialToCompressed.size() + 1, false);
  visited[0] = true;
  // adding all elements in start node
  int startNode = initialToCompressed.at(start);
  std::vector<int> linesInNode = compressedToInitial.at(startNode);
  int index = start - linesInNode[0] - 1;
  for (int i = index; i >= 0; i--) {
    result.emplace_back(linesInNode[i]);
    visited[linesInNode[i]] = true;
  }
  std::queue<int> q;
  q.push(startNode);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    for (int i : compressedCFG[curr]) {
      if (!visited[compressedToInitial.at(
              i)[compressedToInitial.at(i).size() - 1]]) {
        for (int j : compressedToInitial.at(
                 i)) { // adding all elements within current node
          if (!visited[j]) {
            visited[j] = true;
            result.emplace_back(j);
          }
        }
        q.push(i);
      }
    }
  }
  auto cacheRes = nextTReverseCache.emplace(start, std::move(result));
  return cacheRes.first->second;
}

// Getter for Next*(synonym, synonym)
Table CFG::getNextT() {
  Table table{2};
  for (int i = 1; i < initialToCompressed.size() + 1; i++) {
    std::deque<int> result = getNextTForward(i);
    for (int j : result) {
      table.insertRow({std::to_string(i), std::to_string(j)});
    }
  }
  return table;
}

// Getter for Next*(constant, synonym) or Next*(synonym, constant)
Table CFG::getNextT(int start, bool isForward) {
  Table table{1};
  std::deque<int> result;
  if (isForward) {
    result = getNextTForward(start);
  } else {
    result = getNextTReverse(start);
  }
  for (int i : result) {
    table.insertRow({std::to_string(i)});
  }
  return table;
}

// Getter for Next*(constant, constant)
bool CFG::isNextT(int start, int end) {
  return getNextTForward(start, end).size() > 0;
}

// Algorithm for Affects(constant, synonym)
std::deque<int> CFG::getAffectsForward(int start, std::string v) {
  // Use cached results if exists
  if (affectsForwardCache.count(start)) {
    return affectsForwardCache.at(start);
  }
  std::vector<std::vector<int>> compressedCFG = forwardCompressedGraph;
  std::deque<int> results;
  // Initialize visited array
  std::vector<bool> visited(initialToCompressed.size() + 1, false);
  visited[0] = true; // no stmt line 0
  // Add lines in start node to results if modified some variable
  int startNode = initialToCompressed.at(start);
  std::vector<int> linesInNode = compressedToInitial.at(startNode);
  int index = start - linesInNode[0] + 1;
  for (int i = index; i < linesInNode.size(); i++) {
    int node = linesInNode[i];
    if (usesAssignTable.contains({std::to_string(node), v})) {
      results.emplace_back(node);
    }
    if (modifiesTable.contains({std::to_string(node), v})) {
      // v is modified in a line in the start node
      // Cache results
      auto cacheRes = affectsForwardCache.emplace(start, std::move(results));
      return cacheRes.first->second;
    }
    visited[node] = true;
  }
  std::queue<int> q;
  q.push(startNode);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    // Looping through neighbor nodes
    for (int i : compressedCFG[curr]) {
      if (!visited[compressedToInitial.at(i)[0]]) {
        bool isModified = false;
        for (int j : compressedToInitial.at(i)) {
          if (isModified) {
            visited[j] = true;
          }
          if (!visited[j]) {
            visited[j] = true;
            // Add to results if Uses(j, v) is true
            if (usesAssignTable.contains({std::to_string(j), v})) {
              results.emplace_back(j);
            }
            if (modifiesTable.contains({std::to_string(j), v}) &&
                !whileIfTable.contains({std::to_string(j)})) {
              isModified = true;
            }
          }
        }
        // Enqueue only if no line in compressed node modifies v
        if (!isModified) {
          q.push(i);
        }
      }
    }
  }
  // Cache results
  auto cacheRes = affectsForwardCache.emplace(start, std::move(results));
  return cacheRes.first->second;
}

// Algorithm for Affects(synonym, constant)
std::deque<int> CFG::getAffectsReverse(int start, std::string v) {
  // Use cached results if exists
  auto cacheKey = std::make_pair(start, v);
  if (affectsReverseCache.count(cacheKey)) {
    return affectsReverseCache.at(cacheKey);
  }
  std::vector<std::vector<int>> compressedCFG = reverseCompressedGraph;
  std::deque<int> results;
  // Initialize visited array
  std::vector<bool> visited(initialToCompressed.size() + 1, false);
  visited[0] = true; // no stmt line 0
  // Add lines in start node to results if modified some variable
  int startNode = initialToCompressed.at(start);
  std::vector<int> linesInNode = compressedToInitial.at(startNode);
  int index = start - linesInNode[0] - 1;
  for (int i = index; i >= 0; i--) {
    int node = linesInNode[i];
    if (modifiesAssignTable.contains({std::to_string(node), v})) {
      results.emplace_back(node);
    }
    if (modifiesTable.contains({std::to_string(node), v})) {
      // v is modified in any line in the start node
      // Cache results
      auto cacheRes = affectsReverseCache.emplace(cacheKey, std::move(results));
      return cacheRes.first->second;
    }
    visited[node] = true;
  }
  std::queue<int> q;
  q.push(startNode);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    // Looping through neighbor nodes
    for (int i : compressedCFG[curr]) {
      if (!visited[compressedToInitial.at(i).back()]) {
        bool isModified = false;
        auto lines = compressedToInitial.at(i);
        for (int j = lines.size() - 1; j >= 0; j--) {
          int line = lines[j];
          if (isModified) {
            visited[line] = true;
          }
          if (!visited[line]) {
            visited[line] = true;
            // Add to results if Modifies(line, v) and line is assignment stmt
            if (modifiesAssignTable.contains({std::to_string(line), v})) {
              results.emplace_back(line);
            }
            if (modifiesTable.contains({std::to_string(line), v}) &&
                !whileIfTable.contains({std::to_string(line)})) {
              isModified = true;
              break;
            }
          }
        }
        // Enqueue only if no line in compressed node modifies v
        if (!isModified) {
          q.push(i);
        }
      }
    }
  }
  // Cache results
  auto cacheRes = affectsReverseCache.emplace(cacheKey, std::move(results));
  return cacheRes.first->second;
}

// Getter for Affects(constant, constant)
bool CFG::isAffects(int a1, int a2) {
  // Get variable modified in line a1 and used in line a2
  auto modifiesA1Table = modifiesTable;
  modifiesA1Table.setHeader({"a1", "v"});
  modifiesA1Table.filterColumn("a1", {std::to_string(a1)});
  auto usesA2Table = usesTable;
  usesA2Table.setHeader({"a2", "v"});
  usesA2Table.filterColumn("a2", {std::to_string(a2)});
  modifiesA1Table.mergeWith(usesA2Table);
  if (modifiesA1Table.empty()) {
    // No variable modified in line a1 and used in line a2
    return false;
  } else {
    // Continue to get variable
    auto v = *modifiesA1Table.getColumn("v").begin();
    auto result = getAffectsForward(a1, v);
    return std::find(result.begin(), result.end(), a2) != result.end();
  }
}

// Getter for Affects(constant, synonym) or Affects(synonym, constant)
Table CFG::getAffects(int start, bool isForward) {
  Table table{1};
  std::deque<int> result;
  if (isForward) {
    // Affects(k, a) utilizes forwardCompressedGraph, k here is a constant
    auto modifiesATable = modifiesTable;
    modifiesATable.setHeader({"a1", "v"});
    modifiesATable.filterColumn("a1", {std::to_string(start)});
    // modifiesATable has one variable after filter
    auto v = *modifiesATable.getColumn("v").begin();
    result = getAffectsForward(start, v);
  } else {
    // Affects(a, k) utilizes reverseCompressedGraph, k here is a constant
    auto usesATable = usesTable;
    usesATable.setHeader({"a2", "v"});
    usesATable.filterColumn("a2", {std::to_string(start)});
    // usesATable has one or more variables after filter
    std::vector<std::string> variables;
    for (auto data : usesATable.getData({"v"})) {
      variables.emplace_back(data[0]);
    }
    for (auto v : variables) {
      auto partialResults = getAffectsReverse(start, v);
      result.insert(result.end(), partialResults.begin(), partialResults.end());
    }
  }
  for (int i : result) {
    table.insertRow({std::to_string(i)});
  }
  return table;
}

// Getter for Affects(synonym, synonym)
Table CFG::getAffects() {
  Table table{2};
  for (auto data : modifiesAssignTable.getData()) {
    auto result = getAffectsForward(std::stoi(data[0]), data[1]);
    for (int i : result) {
      table.insertRow({data[0], std::to_string(i)});
    }
  }
  return table;
}

// Getter for Affects*(synonym, synonym)
Table CFG::getAffectsT() {
  // Use cached results if exists
  if (affectsTCache.getHeader().size() == 2) {
    return affectsTCache;
  }
  Table table = getAffects();
  table.transitiveClosure();
  // Cache results
  affectsTCache = std::move(table);
  return affectsTCache;
}

void CFG::clearCache() {
  affectsForwardCache.clear();
  affectsReverseCache.clear();
  affectsTCache = Table{1};
}
