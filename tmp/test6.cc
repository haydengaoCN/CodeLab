#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::string file_path = "./json_body";

  std::ifstream in(file_path, std::ifstream::in | std::ifstream::binary);

  std::string str, line;
  while (std::getline(in, line)) {
    std::cout << line << std::endl;
    str += line;
  }
  std::cout << str << std::endl;

  return 0;
}
