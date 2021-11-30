#include <vector>
#include <iostream>

int main() {
  std::vector<int> vec;
  vec.reserve(2);
  std::vector<int*> pvec;
  vec.emplace_back(1);
  pvec.emplace_back(&vec.back());
  vec.emplace_back(2);
  pvec.emplace_back(&vec.back());


  std::cout << pvec.size() << std::endl;
  auto p = pvec[0];
  if (!p) std::cout << "empty ptr" << std::endl;
  std::cout << *p << std::endl;

  return 0;
}
