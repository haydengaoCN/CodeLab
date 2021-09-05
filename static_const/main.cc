#include <iostream>
int main() {
  const int a = 10;
  int b = 20;
  int* const ptr = &b;
  //const int* ptr = &a;
  *ptr = 100;
  ptr = &b;
  std::cout << a << std::endl;
  return 0;
}
