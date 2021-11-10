#include <iostream>
#include <string>
#include <cstring>

void test() {
  char msg[512];
  std::string say_hi = "helloworld";
  memset(msg, 0, sizeof(msg));
  memcpy(msg, say_hi.c_str(), say_hi.size());
  std::cout << say_hi.size() << "," << strlen(msg) << std::endl;

  char val[] = "helloworld";
  std::cout << sizeof(val) << "," << strlen(val) << std::endl;

  char* ptr = val;
  std::cout << strlen(ptr) << std::endl;
}

int main() {
  test();
  return 0;
}
