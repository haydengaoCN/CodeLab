#include <iostream>
#include <string>
#include <cstring>

void test() {
  char msg[512];
  std::string say_hi = "hello";
  memset(msg, 0, sizeof(msg));
  memcpy(msg, say_hi.c_str(), say_hi.size());
  std::cout << say_hi.size() << "," << strlen(msg) << std::endl;

  char val[] = "hello";
  std::cout << sizeof(val) << "," << strlen(val) << std::endl;
}

int main() {
  test();
  return 0;
}
