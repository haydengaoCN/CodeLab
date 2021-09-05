1#include <iostream>

template <int n>
struct factorial {
  static const int value = n * factorial<n-1>::value;
};

template <>
struct factorial<0>
  static const int value = 1;
};


int main() {
  std::cout << factorial<4>::value << std::endl;
  return 0;
}