#include <iostream>
#include <vector>

class A {
 public:
  int get_x() {
    return x;
  }
  int x;
};

int main() {
  A a1, a2;
  std::vector<A> vec;
  vec.push_back(a1);
  vec.push_back(a2);

  auto iter = vec.rbegin()->get_x();

  return 0;
}

