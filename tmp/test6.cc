#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::string file_path = "test.csv";
  std::ofstream out(file_path, std::ios::trunc | std::ios::binary);

  out<< "a\t" << "b\t" << "c\t" << "d\n";
  out<< "1\t" << "2\t" << "3\t" << "4\n";
  out<< "11\t" << "22\t" << "33\t" << "44\n";
  out<< "111\t" << "222\t" << "333\t" << "444\n";


  return 0;
}
