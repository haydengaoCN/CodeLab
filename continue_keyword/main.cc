#include <iostream>

void test(int idx) {
  if (idx == 0) {
    std::cout << 0 << std::endl;
  } else if (idx == 1) {
    continue;
    std::cout << 1 << std::endl;
  } else {
    std::cout << idx << std::endl;
  }
}

int main() {
 test(0);
 test(1);

 return 0;
}
