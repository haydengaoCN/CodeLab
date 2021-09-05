#include <stdio.h>
#include <thread>
#include <string>
#include <iostream>

struct Foo {
  std::string s;
};

void ShowInfoA(const Foo& foo) {
  printf("func A: content-%s, c_str=%p, std:;string-%p\n", foo.s.c_str(), foo.s.c_str(), foo.s);
}

void ShowInfoB(const Foo& foo) {
  printf("func B: content-%s, c_str=%p, std:;string-%p\n", foo.s.c_str(), foo.s.c_str(), foo.s);
}

void test1() {
  Foo foo;
  foo.s = "hello world";
  std::thread tA(ShowInfoA, foo);
  std::thread tB(ShowInfoB, foo);

  tA.join();
  tB.join();
}

void test2() {
  std::string str("test");
  const char* p = str.data();
  printf("before: content-%s, c_str-%p, std::string-%p\n", str.c_str(), str.c_str(), &str);
  {
    const std::string str2(str);
    printf("before: content-%s, c_str-%p, std::string-%p\n", str2.c_str(), str2.c_str(), &str2);
  }
  printf("after: content-%s, c_str-%p, std::string-%p\n", str.c_str(), str.c_str(), &str);
}

int main() {
  test2();
  return 0;
}
