#include <vector>
#include <iostream>
#include <format>

void foo() {
  for (std::vector v{1, 2, 3}; auto& e : v) {
    std::cout << e << ",";
  }
  std::cout << std::endl;
}

// compile:
// g++-11.1.0 -std=c++20 main.cc -o main -Wl,-rpath -Wl,/usr/local/gcc-11.1.0/lib64

int main() {
  foo();
  std::cout << std::format("hello {}!\n", "world");

  return 0;
}
