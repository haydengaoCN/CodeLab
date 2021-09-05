#include<iostream>

void test() {
  size_t flag = 2;
  for (size_t idx = 0; idx < 10; ++idx) {
    std::cout << idx << ", ";
    if (idx == flag) {
      std::cout << "break now" << std::endl;
      break;
    }
  }
  std::cout << "return" << std::endl;
  return;
}

int main() {
  test();

  return 0;
}
