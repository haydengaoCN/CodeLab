#include <iostream>
#include <stdio.h>

class Foo {
 public:
  int a;
  int* ptr;
};

// g++ -std=c++17 test15.cc -o test15 && ./test15
int main() {
  Foo foo;
  if (foo.ptr == nullptr) {
    std::cout << "ptr is nullptr" << std::endl;
  } else {
    std::cout << "ptr is not nullptr" << std::endl;
  }
  printf("%x\n", foo.ptr);

  return 0;
}

