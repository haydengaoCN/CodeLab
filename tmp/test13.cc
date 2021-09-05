#include <vector>
#include <string>
#include <iostream>

bool SplitString(const std::string &src,
    const char *separators,
    std::vector<std::string> *result) {
  result->clear();
  if (src.empty() || separators == NULL) {
    return false;
  }
  static const int kDictLen = 128;  // 0~127
  char dict[kDictLen] = {'\0'};
  const char *p = separators;
  while (*p) {
    const int pvalue = static_cast<int>(*p);
    if (pvalue >= kDictLen || pvalue < 0) {
      return false;
    } else {
      dict[pvalue] = 1;
    }
    ++p;
  }
  size_t last_pos = 0;
  p = src.c_str();
  for (size_t pos = 0; pos < src.size(); ++pos) {
    const int pvalue = static_cast<int>(p[pos]);
    if (pvalue >= kDictLen || pvalue < 0) {
      continue;
    } else if (dict[static_cast<int>(pvalue)]) {
      result->push_back(src.substr(last_pos, pos-last_pos));
      last_pos = pos+1;
    }
  }
  if (last_pos == src.size()) {
    result->push_back("");
  } else {
    result->push_back(src.substr(last_pos));
  }
  return true;
}

int main() {
  std::vector<std::string> vec;
  std::string src = "_hello_world";
  SplitString(src, "_", &vec);

  for (const auto& val : vec) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  return 0;
}
