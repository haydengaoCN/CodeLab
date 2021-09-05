#include <vector>
#include <iostream>

namespace sp1 {

/* constexpr变量 / 内联变量
一个constexpr变量是一个在编译期时完全确定的常数；

C++17 引入了内联（inline）变量的概念，允许在头文件中定义内联变量;
然后像内联函数一样，只要所有的定义都相同，那变量的定义出现多次也没有关系。

ODR : one definition rule 有且只有一个
ODR-use的类静态常量需要有同一个定义，若没有内敛变量需要再一个源代码文件(非头文件)中定义；
*/

struct foo {
  static constexpr int value = 0;  // 变量必须立即初始化
  static const int value2;
  static inline const int value3 = 2;
};
const int foo::value2 = 0;  // 必须被定义一次

void test1() {
  std::vector<int> vec;
  vec.push_back(foo::value);
  vec.push_back(foo::value2);
  vec.push_back(foo::value3);
}

}  // namespace sp1;

namespace sp2 {

/* constexpr函数 / 编译期计算
constexpr函数至少对某一组实参可以在编译期间产生一个编译期常数;
其并不保证在任何情况下都会产生一个编译期常数，因此也可作为普通函数被调用;
(检验的方法是将结果赋给一个constexpr变量)
*/

constexpr int sqr(int n) {
  return n * n;
}

constexpr int factorial(int n) {
  return n == 0 ? 1 : n * factorial(n-1);
}

void test2() {
  constexpr int val1 = sqr(3);
  constexpr int val2 = factorial(3);
  std::cout << val1 << ", " << val2 << std::endl;
}

}  // namespace sp2

namespace sp3 {

/* constexpr vs. const
1. 含义
  const: 运行时常量;
  constexpr: 编译时常量，并且也不能修改；// 可以理解为比const多了一个编译时为常量的限制;
2. 用法/位置
  const位置影响含义: 1) const char* -> a pointer to a const char; 2) char* const -> a const pointer to a char;
  constexpr位置无关，一般放在最前面即可;
*/
void test() {
  const int val = 2;
  constexpr int val2 = val;
}

}  // namespace sp3

int main() {
  sp2::test2();
  return 0;
}