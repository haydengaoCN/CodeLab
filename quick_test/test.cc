#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string dir_path = "../log/";
  std::string file_path = dir_path + "tmp.txt";
  std::ofstream out(file_path, std::ios::out);
  if (out.is_open()) {
    std::cout << "log file to:" << file_path << std::endl;
    out << "test only\n";
    out.close();
  }
  return 0;
}
