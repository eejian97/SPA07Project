#include "PQLParser.h"
#include <iterator>

using Lexer::Token;
using Lexer::TokenType;

namespace Parser {
Lexer::Token PQLParser::expect(Lexer::Token token) {
  if (tokens.empty()) {
    throw std::logic_error("Expected more tokens but ran out");
  }
  if ((token.type == TokenType::Identifier && token.value.empty() &&
       tokens.front().type == TokenType::Identifier) ||
      (token.type == TokenType::Number && token.value.empty() &&
       tokens.front().type == TokenType::Number) ||
      tokens.front() == token) {
    auto t = tokens.front();
    tokens.pop_front();
    return t;
  }
  throw std::logic_error("Expected " + token.value +
                         " but got: " + tokens.front().value);
  return token;
}

void PQLParser::parseQuery() {
  while (tokens.front().value != "Select") {
    parseDeclaration();
  }
  expect(PQLTokens::Select);
  parseResultCl();
  if (!tokens.empty()) {
    parseClauses();
  }
}

void PQLParser::parseDeclaration() {
  auto designEntityToken = expect(PQLTokens::Identifier);
  if (designEntityToken.value == "prog") {
    expect(PQLTokens::Underscore);
    expect(PQLTokens::Line);
  }
  if (PQLTokens::tokenEntityMap.count(designEntityToken) == 0) {
    throw std::logic_error("Invalid declaration");
  }
  auto synonymToken = expect(PQLTokens::Identifier);
  declarations.emplace(std::make_pair(
      synonymToken.value, PQLTokens::tokenEntityMap.at(designEntityToken)));
  while (tokens.front() != PQLTokens::Semicolon) {
    expect(PQLTokens::Comma);
    auto synonymToken = expect(PQLTokens::Identifier);
    declarations.emplace(std::make_pair(
        synonymToken.value, PQLTokens::tokenEntityMap.at(designEntityToken)));
  }
  expect(PQLTokens::Semicolon);
}

void PQLParser::parseClauses() {
  if (tokens.front() == PQLTokens::With) {
    parseWithCl();
  } else if (tokens.front() == PQLTokens::Pattern) {
    parsePatternCl();
  } else if (tokens.front() == PQLTokens::Such) {
    parseSuchThatCl();
  } else {
    throw std::logic_error("Unexpected clause: " + tokens.front().value);
  }
}

void PQLParser::parseResultCl() {
  if (tokens.front() == PQLTokens::Boolean) {
    expect(PQLTokens::Boolean);
    query.selectors.push_back(QueryEntity(QueryEntityType::Boolean));
  } else {
    parseTuple();
  }
}

void PQLParser::parseTuple() {
  if (tokens.front().type == TokenType::Identifier) {
    query.selectors.push_back(parseElem());
  } else {
    expect(PQLTokens::LeftChevron);
    query.selectors.push_back(parseElem());
    while (tokens.front() != PQLTokens::RightChevron) {
      expect(PQLTokens::Comma);
      query.selectors.push_back(parseElem());
    }
    expect(PQLTokens::RightChevron);
  }
}

void PQLParser::parseWithCl() {
  expect(PQLTokens::With);
  parseAttrCond();
}

void PQLParser::parseAttrCond() {
  parseAttrCompare();
  while (tokens.front() == PQLTokens::And) {
    expect(PQLTokens::And);
    parseAttrCompare();
  }
}

void PQLParser::parseAttrCompare() {
  auto attrRef1 = parseRef();
  expect(PQLTokens::Equals);
  auto attrRef2 = parseRef();

  Clause withCl(ClauseType::With, {attrRef1, attrRef2});
  query.clauses.push_back(withCl);
}

void PQLParser::parseSuchThatCl() {
  expect(PQLTokens::Such);
  expect(PQLTokens::That);
  parseRelCond();
}

void PQLParser::parseRelCond() {
  parseRelRef();
  while (tokens.front() == PQLTokens::And) {
    expect(PQLTokens::And);
    parseRelRef();
  }
}

void PQLParser::parseRelRef() {
  // Alt type determines if the clause is of an "alternate type"
  // For Parent, Follows, Call, Next, Affects, the alt type is transitive
  // closure
  // Irrelevant for Uses and Modifies
  bool altType = false;

  auto relWord = expect(PQLTokens::Identifier);
  // Determine relation and alt type for transitive closure
  if (PQLTokens::transitiveRel.count(relWord) &&
      tokens.front() == PQLTokens::Star) {
    expect(PQLTokens::Star);
    altType = true;
  }
  expect(PQLTokens::LeftParentheses);
  auto ref1 = parseGenRef();
  expect(PQLTokens::Comma);
  auto ref2 = parseGenRef();
  expect(PQLTokens::RightParentheses);

  if (PQLTokens::relClauseMap.count(std::make_pair(relWord, altType))) {
    throw std::logic_error("Invalid relation specified");
  }

  ClauseType clType =
      PQLTokens::relClauseMap.at(std::make_pair(relWord, altType));
  Clause suchThatCl(clType, {ref1, ref2});
  validateSuchThatCl(suchThatCl);
  query.clauses.push_back(suchThatCl);
}

void PQLParser::validateSuchThatCl(Clause suchThatCl) {
  auto allowedRefTypes =
      PQLTokens::allowedRefTypesMap.at(suchThatCl.clauseType);
  validateRef(suchThatCl.parameters[0], allowedRefTypes.first);
  validateRef(suchThatCl.parameters[1], allowedRefTypes.second);
  if ((suchThatCl.clauseType == ClauseType::UsesS ||
       suchThatCl.clauseType == ClauseType::ModifiesS) &&
      (suchThatCl.parameters[0].type == QueryEntityType::Underscore)) {
    throw std::logic_error("First param of uses/modifies cannot be _");
  }
}

void PQLParser::validateRef(QueryEntity ref, PQLTokens::RefType refType) {
  if (!PQLTokens::refTypeSpecificTypesMap.at(refType).count(ref.type)) {
    throw std::logic_error("Invalid ref");
  }
}

void PQLParser::parsePatternCl() {
  expect(PQLTokens::Pattern);
  parsePatternCond();
}

void PQLParser::parsePatternCond() {
  parsePattern();
  while (tokens.front() == PQLTokens::And) {
    expect(PQLTokens::And);
    parsePattern();
  }
}

void PQLParser::parsePattern() {
  auto syn = parseSynonym();
  switch (syn.type) {
  case QueryEntityType::Assign:
    parseAssign();
    break;
  case QueryEntityType::While:
    parseWhile();
    break;
  case QueryEntityType::If:
    parseIf();
    break;
  default:
    throw std::logic_error("Invalid pattern synonym");
  }
}

void PQLParser::parseAssign() {
  expect(PQLTokens::LeftParentheses);
  auto entRef = parseEntRef();
  expect(PQLTokens::Comma);
  auto exprRef = parseExprSpec();
  expect(PQLTokens::RightParentheses);

  Clause patternCl(ClauseType::AssignPatt, {entRef, exprRef});
  query.clauses.push_back(patternCl);
}

void PQLParser::parseWhile() {
  expect(PQLTokens::LeftParentheses);
  auto entRef = parseEntRef();
  expect(PQLTokens::Comma);
  expect(PQLTokens::Underscore);
  expect(PQLTokens::RightParentheses);

  Clause patternCl(ClauseType::WhilePatt, {entRef});
  query.clauses.push_back(patternCl);
}

void PQLParser::parseIf() {
  expect(PQLTokens::LeftParentheses);
  auto entRef = parseEntRef();
  expect(PQLTokens::Comma);
  expect(PQLTokens::Underscore);
  expect(PQLTokens::Comma);
  expect(PQLTokens::Underscore);
  expect(PQLTokens::RightParentheses);

  Clause patternCl(ClauseType::IfPatt, {entRef});
  query.clauses.push_back(patternCl);
}

QueryEntity PQLParser::parseExprSpec() {
  QueryEntity ent;
  std::string expr = "";
  std::list<Token> exprTokens;
  if (tokens.front() == PQLTokens::Underscore) {
    expect(PQLTokens::Underscore);
    if (tokens.front() == PQLTokens::Quote) {
      expr = parseQuotedExpr();
      expect(PQLTokens::Underscore);
      expr = "_" + expr + "_";
    } else {
      ent.type = QueryEntityType::Underscore;
      ent.name = "_";
    }
  } else {
    expr = parseQuotedExpr();
  }
  ent.type = QueryEntityType::Expression;
  ent.name = expr;
}

std::string PQLParser::parseQuotedExpr() {
  std::list<Token> exprTokens;
  std::string expr = "";
  expect(PQLTokens::Quote);
  if (tokens.front() == PQLTokens::Quote) {
    return expr;
  } else {
    while (tokens.front() != PQLTokens::Quote) {
      exprTokens.push_back(tokens.front());
      tokens.pop_front();
    }
    expr = Parser::tokensToString(Parser::parseExpr(exprTokens));
  }
  return expr;
}

QueryEntity PQLParser::parseAttrRef() {
  auto ent = parseSynonym();
  expect(PQLTokens::Period);
  auto attrToken = expect(PQLTokens::Identifier);
  if (attrToken.value != "varName" && attrToken.value != "procName" &&
      attrToken.value != "stmt") {
    throw std::logic_error("Unexpected attribute");
  }
  ent.name += "." + attrToken.value;
  if (attrToken == PQLTokens::Stmt) {
    expect(PQLTokens::Hash);
    ent.name += "#";
  }
  ent.attrRefSynonymType = ent.type;
  ent.type = QueryEntityType::Attrref;
  return ent;
}

QueryEntity PQLParser::parseRef() {
  if (tokens.front() == PQLTokens::Quote) {
    return parseName();
  } else if (tokens.front().type == TokenType::Number) {
    return parseLineNo();
  } else if (*std::next(tokens.begin()) == PQLTokens::Period) {
    return parseAttrRef();
  } else {
    auto syn = parseSynonym();
    if (syn.type != QueryEntityType::Progline) {
      throw std::logic_error("Synonym must be of type prog_line");
    }
    return syn;
  }
}

QueryEntity PQLParser::parseGenRef() {
  if (tokens.front() == PQLTokens::Underscore) {
    return parseUnderscore();
  } else if (tokens.front() == PQLTokens::Quote) {
    return parseName();
  } else if (tokens.front() == PQLTokens::Number) {
    return parseLineNo();
  } else {
    return parseSynonym();
  }
}

QueryEntity PQLParser::parseEntRef() {
  if (tokens.front() == PQLTokens::Underscore) {
    return parseUnderscore();
  } else if (tokens.front() == PQLTokens::Quote) {
    return parseName();
  } else {
    return parseSynonym();
  }
}

QueryEntity PQLParser::parseStmtRef() {
  if (tokens.front() == PQLTokens::Underscore) {
    return parseUnderscore();
  } else if (tokens.front() == PQLTokens::Number) {
    return parseLineNo();
  } else {
    return parseSynonym();
  }
}

QueryEntity PQLParser::parseLineRef() {
  if (tokens.front() == PQLTokens::Underscore) {
    return parseUnderscore();
  } else if (tokens.front() == PQLTokens::Number) {
    return parseLineNo();
  } else {
    return parseSynonym();
  }
}

QueryEntity PQLParser::parseElem() {
  if (*std::next(tokens.begin()) == PQLTokens::Period) {
    return parseAttrRef();
  } else {
    return parseSynonym();
  }
}

QueryEntity PQLParser::parseSynonym() {
  auto synToken = expect(PQLTokens::Identifier);
  if (!(declarations.count(synToken.value))) {
    throw std::logic_error("Synonym " + synToken.value + " not declared");
  }
  QueryEntity ent;
  ent.name = synToken.value;
  ent.type = declarations.at(synToken.value);
  return ent;
}

QueryEntity PQLParser::parseUnderscore() {
  expect(PQLTokens::Underscore);
  QueryEntity ent;
  ent.name = "_";
  ent.type = QueryEntityType::Underscore;
  return ent;
}

QueryEntity PQLParser::parseLineNo() {
  auto noToken = expect(PQLTokens::Number);
  QueryEntity ent;
  ent.name = noToken.value;
  ent.type = QueryEntityType::Line;
  return ent;
}

QueryEntity PQLParser::parseName() {
  expect(PQLTokens::Quote);
  auto nameToken = expect(PQLTokens::Identifier);
  expect(PQLTokens::Quote);
  QueryEntity ent;
  ent.name = nameToken.value;
  ent.type = QueryEntityType::Name;
  return ent;
}

PQLParser::PQLParser(std::list<Lexer::Token> tokens) : tokens(tokens) {
  parseQuery();
}

Query PQLParser::getQuery() { return query; }

Query parsePQL(std::list<Token> tokens) { return PQLParser(tokens).getQuery(); }
} // namespace Parser
