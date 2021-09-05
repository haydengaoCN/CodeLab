#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

void test1() {
  std::time_t t = std::time(0);  // t is an integer type
  // std::cout << t << " seconds since 01-Jan-1970\n";

  std::string file_name = "/data/home/haydengao/time_" + std::to_string(t);
  std::ofstream out(file_name, std::ios::trunc | std::ios::binary);
  if (out.is_open()) {
    out << t << std::endl;
    out.close();
  } else {
    std::cout << "can't open file!" << std::endl;
  }
}

void test2() {
  // std::ofstream out("/data/time.txt", std::ios::trunc | std::ios::binary);
  std::ofstream out("contract_query.txt", std::ios::trunc | std::ios::binary);
  out << "hello" << std::endl;
  out.close();
}

void test3() {
  auto t1 = time(nullptr);
  auto t2 = "1618386013";
  std::cout << t1 << std::endl;
  std::cout << t2 << std::endl;
  time_t tt2 = std::stoi(t2);
  std::cout << tt2 << std::endl;
	std::cout << "delay:" << t1 - tt2 << "(s)" << std::endl;
}
int main() {
  test3();
  return 0;
}
