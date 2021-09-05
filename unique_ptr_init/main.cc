#include <iostream>
#include <memory>

int main() {
  auto uptr = std::make_unique<std::string>("hello");
  std::cout << *uptr;
  return 0;
}
