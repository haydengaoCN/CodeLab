#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::unordered_map<std::string, std::string> umap;
  umap.emplace("a", "A");
  umap.emplace("b", "B");
  umap.emplace("e", "E");
  umap.emplace("ab", "AB");

  for (const auto& [v1, v2] : umap) {
    std::cout << v1 << "," << v2 << std::endl;
  }

  std::vector<int> vec;
  vec.emplace_back(1);
  vec.emplace_back(3);
  vec.emplace_back(2);

  for (const auto& val : vec) {
    std::cout << val << std::endl;
  }

  return 0;
}


