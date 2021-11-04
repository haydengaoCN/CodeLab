#include <iostream>

int main() {
  char* aid = "3099748342";
  uint64_t val1 = atoi(aid);
  uint64_t val2 = atol(aid);
  std::cout << aid << ":" << val1 << ":" << val2 << std::endl;
  return 0;
}
