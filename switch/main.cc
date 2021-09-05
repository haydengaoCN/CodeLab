#include <iostream>
#include <vector>
#include <string>

int main() {
  std::vector<std::string> str_list{"case1", "case2", "case4"};
  for (const auto& val : str_list) {
    switch (val) {
      case "case1":
        std::cout << val << std::endl;
				break;
      case "case2":
        std::cout << val << std::endl;
				break;
      case "case3":
        std::cout << val << std::endl;
				break;
      case "case4":
        std::cout << val << std::endl;
				break;
      default:
				std::cout << "default" << std::endl;
    }
  }
  return 0;
}
