#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

using NewOldValue = std::pair<std::string, std::string>;
// field -> new/old value
using FieldValueTuples = std::unordered_map<std::string, NewOldValue>;

int main() {
  std::shared_ptr<FieldValueTuples> tuples_;
  tuples_ = std::make_shared<FieldValueTuples>();
  tuples_->emplace("db", std::make_pair<std::string, std::string>("new", "old"));

  return 0;
}

