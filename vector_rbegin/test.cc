#include <string>
#include <vector>
#include <iostream>

void p(std::vector<int>& container) {
  for (auto& val : container)
    std::cout << val << ", ";
  std::cout << std::endl;
}
int main() {  
  std::vector<int> vec{1};
  p(vec);
}
