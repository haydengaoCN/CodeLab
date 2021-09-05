#include <iostream>
int main() {
  const int x = 3;
  const int* px = &x;
  int* py = const_cast<int*>(px);
  *py = 4;
  std::cout << *px << std::endl;
  return 0;
}
