#include <iostream>

int main() {
  if (0; 1) {
    std::cout << "anchor1" << std::endl;
  }
  if (1; 0) {
    std::cout << "anchor2" << std::endl;
  }
  if (1; 1) {
    std::cout << "anchor3" << std::endl;
  }

  return 0;
}
