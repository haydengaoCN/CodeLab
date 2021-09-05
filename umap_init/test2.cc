#include <iostream>
#include <unordered_map>
#include <map>
#include <string>

int main() {
  const std::unordered_map<std::string, int> umap = { {"one", 1}};
  
  for (const auto& [key, value] : umap) {
	  std::cout << key << value << std::endl;
  }

 return 0;
}
