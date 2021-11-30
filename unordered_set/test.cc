#include <iostream>
#include <unordered_set>

int main() {
  std::unordered_set<int> uset{1, 2, 3};
  auto ptr = &uset;
  for_each(ptr->begin(), ptr->end(), [](const auto& v) { std::cout << v << ",";});
  std::cout<< std::endl;
  return 0;
}
