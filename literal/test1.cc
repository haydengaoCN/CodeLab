#include <chrono>
#include <complex>
#include <iostream>
#include <string>
#include <thread>

/*
C++易用性
1. 字面量
  已有字面量：
    "hello" 字符串字面量, 表示 const char[6];
    1 整数字面量, int类型;
    0.0 浮点数字面量, 类型是double;
    3.14f 浮点数字面量,类型为float;
    123ul, 无符号长整形, unsigned long;
  自定义字面量：
    可以通过重载 operator "" 实现
2. 进制字面量
  0x 16进制字面量；HEX
  0   8进制字面量；OCT
  0b  2进制
3. 数字分割符
  '
4. 静态断言static-assert
  编译时检查假设是否成立

字面类型类：
  1) 一个类的构造函数只包含常量表达式，满足对constexpr函数的限制(不包含任何动态分配内存);
  2) 类的析构函数是平凡的；（不进行任何动作的析构函数）
*/
void foo() {
  using namespace std::literals::chrono_literals;
  using namespace std::literals::complex_literals;
  using namespace std::literals::string_literals;
  std::cout << "i * i = " << 1i * 1i << std::endl;
  std::cout << "Waiting for 500ms" << std::endl;
  std::this_thread::sleep_for(500ms);
  std::cout << "Hello world"s.substr(0, 5) << std::endl;
}


struct length {
  double value;
  enum unit {
    metre,
    kilometre,
    millimetre,
    centimetre,
    inch,
    foot,
    yard,
    mile,
  };
  static constexpr double factors[] =
    {1.0,    1000.0,  1e-3,
     1e-2,   0.0254,  0.3048,
     0.9144, 1609.344};
  explicit length(double v,
                  unit u = metre)
  {
    value = v * factors[u];
  }
};

length operator+(length lhs,
                 length rhs)
{
  return length(lhs.value +
                rhs.value);
}

length operator"" _m(long double v)
{
  return length(v, length::metre);
}

length operator"" _cm(long double v)
{
  return length(v, length::centimetre);
}

void foo2() {
  auto x = 1.0_m + 2.0_cm;
  std::cout << x.value << std::endl;
}

void foo3() {
  unsigned mask = 0b111'000'000;
  long r = 6'378'137;
  double pi = 3.141592653'589'7'93;
  const unsigned magic = 0x44'42'47'4E;
  std::cout << "mask:" << mask << std::endl
            << "r:" << r << std::endl
            << "pi:" << pi << std::endl
            << "magic:" << magic << std::endl;
}

void foo4() {
  static_assert(1 != 2, "1 -= 2");  // check when compile
}

int main() {
  foo3();
}