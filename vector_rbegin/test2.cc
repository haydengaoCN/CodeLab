#include <vector>
#include <iostream>

int main() {
  std::vector<int> vec;
  vec.reserve(0);
  vec.emplace_back(12);
 
  for (const auto& val: vec)
    std::cout << val << std::endl;
  return 0;
}
