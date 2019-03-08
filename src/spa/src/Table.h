#pragma once
#include <set>
#include <vector>

class Table {
  typedef std::vector<std::string> HeaderRow;
  typedef std::vector<std::string> DataRow;

private:
  HeaderRow headerRow;
  std::set<DataRow> data;

public:
  Table(HeaderRow headers);
  void insertRow(DataRow row);
  std::set<DataRow> getCols(HeaderRow cols) const;
  bool empty() const;
  void mergeWith(Table other);
};