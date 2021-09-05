#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace variadic_template {

/* 可变模板 variadid template
在模板参数里表达不定个数和不定类型，用途：
  1）用于在通用工具模板中转发参数到另外一个函数；
  2）在递归的模板中表达通用的情况（另外会有至少一个模板特化来表达边界情况）

1）转发
template <typename T, typename... args>
inline unique_ptr<T> make_unique<Args&&... args> {
  return unique_ptr<T>(new T(forward<Args>(args)...));
}
2）递归用法 - 实现编译期递归

*/

template <typename T>
constexpr auto sum(T x) {
  return x;
}

template <typename T1, typename T2, typename... Targ>
constexpr auto sum(T1 x, T2 y, Targ... args) {
  return sum(x + y, args...);
}

void test() {
  std::cout << sum(10, 1.1, 1.2) << std::endl;
}

}  // namespace variadid_template

namespace tuple_basic {

/* tuple 多元组模板
可以认为是pair的一般化，能表达任一多个固定数目，固定类型值得组合。
*/

using num_tuple = std::tuple<int, std::string, std::string>;

std::ostream& operator << (std::ostream& os, const num_tuple& value) {
  os << std::get<0>(value) << "," << std::get<1>(value) << "," << std::get<2>(value);
  return os;
}

void test() {
  std::vector<num_tuple> vn{
    {1, "one", "un"},
    {2, "two", "deux"},
    {3, "three", "trois"},
    {4, "four", "quatre"}
  };
  std::get<2>(vn[0]) = "une";
  std::sort(vn.begin(), vn.end(), [](const auto& left, const auto& right)
      {return std::get<2>(left) < std::get<2>(right);});
  for (auto&& t : vn) {
    std::cout << t << std::endl;
    const auto& [idx, eng, france] = t;
    std::cout << idx << "," << eng << "," << france << std::endl;
  }
  std::cout << "tuple size:" << std::tuple_size_v<num_tuple> << std::endl;
}

}  // namespace tupel_basic

int main() {
  variadic_template::test();
  tuple_basic::test();

  return 0;
}