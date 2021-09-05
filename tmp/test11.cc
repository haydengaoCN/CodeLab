#include <iostream>

struct A {  // 12
  char a;
  int b;
  short c;
};
struct B {  // 8
  int b;
  char a;
  short c;
};

struct C { // 7 空间是节省下来了，但是会影响读取的速度。
  char a;
  int b;
  short c;
} __attribute__((packed));

int main() {
  C sample_c;
  sample_c.a = 'a';
  sample_c.b = 1;
  sample_c.c = 2;

  std::cout << sample_c.a << "," << sample_c.b << "," << sample_c.c << std::endl;
  return 0;
}
