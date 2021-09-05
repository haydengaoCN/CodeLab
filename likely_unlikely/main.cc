#include<stdlib.h>
#include<time.h>

#include<iostream>

#define likely(x) __builtin_expect(!!(x), 1) //gcc内置函数, 帮助编译器分支优化
#define unlikely(x) __builtin_expect(!!(x), 0)

int main() {
  srand(time(nullptr));
  int x = rand();

  if (x == 3) {
    x = x + 0xff;
  } else {
    x = x - 0xee;
  }

  std::cout << x << std::endl;

  return 0;
}
