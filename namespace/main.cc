#include <iostream>

namespace app {
namespace qzap {

  void test() {
    std::cout << "app::qzap" << std::endl;
  }

}
}

namespace app {
namespace qzap {

  void test2() {
    test();
  }

}
}


int main() {
  using app::qzap::test;
  test();
  return 0;
}
