#include <iostream>
#include <string>

int main() {
  uint32_t x = 0x12345678;
  char* px_0 = reinterpret_cast<char*>(&x);
  for (auto idx = 0; idx < 4; ++idx) {
    std::cout << (&px_0[idx]) << ":" << std::to_string(px_0[idx]) << std::endl;
  }
}
