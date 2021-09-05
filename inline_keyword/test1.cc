#include "test1.h"

#include <iostream>
#include <vector>

void test1() {
  std::cout << foo::x << " from test1" << std::endl;  // non ODR-use
  std::vector<int> vec;
  vec.push_back(foo::x);  // ODR use
}
