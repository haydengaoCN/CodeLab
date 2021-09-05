#include "test2.h"

#include <vector>
#include <iostream>

void test2() {
  std::cout << foo::x << " from test2" << std::endl;
  std::vector<int> vec;
  vec.push_back(foo::x);
}
