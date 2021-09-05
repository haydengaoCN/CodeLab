#include <iostream>
#include <typeinfo>
#include <vector>
#include <set>
#include <unordered_map>

#include <boost/type_index.hpp>

/*
template<typename T>
void foo(ParamType param)

case1:ParamType不为引用或者指针，即 void foo(T Param),
      1）忽略expr的reference part, 2) 在1）的基础上，如果还有const/volatile，则同样忽略；
case2:ParamType为引用或者指针，但并非Universal Reference, 即 void foo(T& Param) or void foo(T* param),
      1）忽略expr的reference part, 2) 在1）的基础上pattern match;
case3:ParamType为Universal Reference, 即 void foo(T&& Param),
      1) 如果expr为左值，则T和ParamType将会被推断为左值引用，2）如果expr为右值，则采用case1的处理方法；

*/
template<typename T>
void f(T param) {
  std::cout << "type T is deduced to " << typeid(param).name() << std::endl;
}

void f1(const char* param) {
}

void test0() {
  const char* const ptr = "Fun with pointes";
  auto ptr1 = ptr;
  const auto ptr2 = ptr;
  std::cout << typeid(ptr).name() << " " << typeid(ptr1).name() << " " << typeid(ptr2).name() << std::endl;
  std::vector<bool> bool_vec{false, true};
  std::vector<size_t> ut_vec{0, 1};
  for (auto idx = 0; idx < bool_vec.size(); ++idx) {
    std::cout << bool_vec[idx] << " " << typeid(bool_vec[idx]).name() << std::endl;
  }
  for (auto idx = 0; idx < ut_vec.size(); ++idx) {
    std::cout << ut_vec[idx] << " " << typeid(ut_vec[idx]).name() << std::endl;
  }

  f(ptr);
  f1(ptr);
}

class Wiget {
 public:
  Wiget() {

  }
};
/*
template<typename T>
void f2(const T& param) {
  using std::cout;
  using boost::typeindex::type_id_with_cvr;
  // show T
  cout << "T = " << type_id_with_cvr<T>().pretty_name() << '\n';
  // show param's type
  cout << "param = " << type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
 }

void test2() {
  std::vector<Wiget> vw{Wiget(), Wiget()};
  f2(&vw[0]);
 }
*/

void test3() {
 std::unordered_map<uint32_t, uint32_t> umap;
 umap[100] = 1;

 auto& count = umap[100];
 count -= 1;

 std::cout << "umap[100]:" << umap[100] << std::endl;

}

/*
  decltype is an odd creature.
  Given a name or an expression, decltype tells you the name’s or the expression’s type.
  In C++11, the primary use for decltype is declaring function templates
  where the function’s return type depends on its parameter types.
  decltype keeps all characteristic of expression including reference, const and volatie.
*/
template<typename Container, typename Index>
auto AuthAndAccess(Container& c, Index i) -> decltype(c[i]) {  // C++11
  return c[i];
}

/*
  auto specifies that the type is to be deduced,
  and decltype says that decltype rules should be used during the deduction.
  1) decltype rules是为了保证reference这个特性不被auto过滤
  2) 存在的一个问题是，若是C是一个右值，则返回值dangle
*/
template<typename Container, typename Index>
decltype(auto) AuthAndAccess2(Container& c, Index i) {  // C++14
  return c[i];
}

template<typename Container, typename Index>
decltype(auto) AuthAndAccess3(Container&& c, Index i) {  // final C++14 version
  return std::forward<Container>(c)[i];
}

/*
  For lvalue expressions more complicated than names, however, decltype ensures that the type reported is always lvalue refernece.
  Putting parentheses around a name can change the type that decltype reports for it!
  "()" is an expression.
  e-g:
    int x = 0;
    decltype(x) => int
    decltype((x)) => int&
*/
decltype(auto) foo1() {  // return int
  int x = 0;
  return x;
}

decltype(auto) foo2() {  // return int&
  int x = 0;
  return (x);
}

void test4() {
  std::vector<double> vec{1.0, 2.0, 3.0};
  AuthAndAccess(vec, 0)  += 10;
  AuthAndAccess2(vec, 1) += 100;
  AuthAndAccess3(vec, 2) += 1000;

  for (const auto& val : vec) {
    std::cout << val << ", ";
  }
  std::cout << std::endl;
}


/*
  右值
*/
class FOO {
 public:
  FOO(const std::vector<int>& container) : ptr(&container) {}
  const std::vector<int>* const ptr;
};

void test5() {
  FOO foo({1, 2, 3});
  for (auto& val : *(foo.ptr)) {
    std::cout << val << ", ";
  }
  std::cout << std::endl;
}

namespace universal_reference {

template <typename T>
void foo(T&& t) {
  std::cout << tyepid(t).name() << std::endl;
}

void test() {
  int lvalue = 42;
  int& lvalue_ref = lvalue;

  foo(lvalue);
  foo(42);
  foo(lvalue_ref);
}

}  // universal_reference


int main() {
  universal_reference::test();
  return 0;
}
