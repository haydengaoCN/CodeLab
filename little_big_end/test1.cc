#include <iostream>
#include <stdio.h>

union Foo {
  uint8_t  low0;
  uint16_t low1;
  uint32_t low3;
};

void ShowAddr(uint32_t base) {
  char* p0 = reinterpret_cast<char*>(&base);

  std::cout << "p3:" << static_cast<int>(*(p0 + 3)) << std::endl;
  std::cout << "p2:" << static_cast<int>(*(p0 + 2)) << std::endl;
  std::cout << "p1:" << static_cast<int>(*(p0 + 1)) << std::endl;
  std::cout << "p0:" << static_cast<int>(*(p0 + 0)) << std::endl;
}

uint32_t Host2Nl(uint32_t base) {
  return ((base & 0x000000FF) << 24) + ((base & 0x0000FF00) << 8) + ((base & 0x00FF0000) >> 8) + ((base & 0xFF000000) >> 24);
}

int main() {
  uint32_t base = 0x12345678;
  ShowAddr(base);
  ShowAddr(Host2Nl(base));

  return 0;
}
