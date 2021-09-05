#include <vector>
#include <iostream>
#include <functional>

int main() {
  int a = 0, b = 1;
  std::vector<std::reference_wrapper<int>> nums;
  nums.emplace_back(a);
  nums.emplace_back(b);
  
  for (const auto& val : nums) {
    std::cout << val << ",";
  }
  std::cout << std::endl;

  a = 3, b= 4;

  for (const auto& val : nums) {
    std::cout << val << ",";
  }
  std::cout << std::endl;
}
