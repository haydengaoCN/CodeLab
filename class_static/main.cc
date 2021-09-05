#include <iostream>

class A {
 public:
  static int test() {
    std::cout << static_va << std::endl;
    return 0;
  }
  static int set_va(int va_) {
    static_va = va_;
    return 0;
  }

 private:
  static int static_va;
};

int A::static_va = 0;

int main() {
  A::set_va(1);
  A::test();

  return 0;
}
