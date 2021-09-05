#include "test2.h"

#include <iostream>

namespace sp2 {

#include "singleton1.h"

class foo {
 public:
  void Greet() {
    std::cout << "hello world from sp2" << std::endl;
  }
};

void test() {
  singleton_default<foo>::Instance().Greet();
}

}  // namespace sp2