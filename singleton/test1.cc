#include "test1.h"

#include <iostream>

namespace sp1 {

#include "singleton1.h"

class foo {
 public:
  void Greet() {
    std::cout << "hello world from sp1" << std::endl;
  }
};

void test() {
  singleton_default<foo>::Instance().Greet();
}

}  // namespace sp1