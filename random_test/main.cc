#include <stdlib.h>
#include <iostream>

int main() {
  srand((unsigned)(time(nullptr)));

  for (auto idx = 0; idx < 10; ++idx) {
    auto rand_val = (rand() % 5) * 100 + 1000;
    std::cout << rand_val << ", ";
  }
  std::cout << std::endl;
}
