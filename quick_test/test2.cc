#include <iostream>
#include <stdio.h>

union UN {
  int x;
  char addr[sizeof(int)];
};

void test() {
  UN un;
  un.x = 0x12345678;
  std::cout << int(un.addr[0]) << std::endl;
}

bool IsBigEnd() {
  int tmp = 0x12345678;
  char* ch = (char*)(&tmp);
  return (int)(*ch) == 0x12;
}

int main() {
  //IsBigEnd();
  test();
  return 0;
}