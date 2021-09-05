#include <iostream>

int test(int data) {
  static int tmp = data;
  return tmp;
}

int main() {
  char tmp1[] = "123";
  char tmp2[] = "456";
  std::cout << test(1) << std::endl;
  std::cout << test(2) << std::endl;
 
  return 0;
}
