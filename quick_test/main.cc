#include <iostream>
#include <string.h>
#include <string>

int main() {
  std::pair<std::string, std::string> tmp;
  auto& [key, val] = tmp;
  key = "1";
  val = "one";
  std::cout << tmp.first << ", " << tmp.second << std::endl;

  return 0;
}
