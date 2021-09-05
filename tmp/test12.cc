#include <iostream>

struct A {
};

void foo(const A& a){}

void boo(A& a) {
  foo(a);
}

int main() {
  A a;
  boo(a);
  return 0;
}
