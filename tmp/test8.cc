#include <iostream>
#include <string>

auto GetRetVal(int x) {
  if (x > 0) {
    return std::string("");
  }
  return -1;
}

int main () {
  std::cout << GetRetVal(1) << std::endl;
  std::cout << GetRetVal(0) << std::endl;
  return 0;
}
