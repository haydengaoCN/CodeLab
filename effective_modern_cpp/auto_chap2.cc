#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

/*===========================================auto examples========================================*/
void* operator new (const size_t allocated_size) {
  auto address = malloc(allocated_size);
  std::cout << "allocated size:" << allocated_size << ", address:" << address << std::endl;
  return malloc(allocated_size);
}

void operator delete (void* ptr) {
  std::cout << "free memory:" << ptr << std::endl << std::endl;
  free(ptr);
}

void test1() {
  std::unordered_map<std::string, uint32_t> umap;
  auto p1 = std::make_pair<std::string, uint32_t>("one", 1);
  auto p2 = std::make_pair<std::string, uint32_t>("two", 2);
  std::cout << "p1 address:" << &p1 << ", p2 address:" << &p2 << std::endl;
  std::cout << "address:" << &p1 << ", first:" << &(p1.first) << ", second:" << &(p1.second) << std::endl;
  std::cout << "address:" << &p2 << ", first:" << &(p2.first) << ", second:" << &(p2.second) << std::endl;
  umap.emplace(p1);
  umap.emplace(p2);

  for (const std::pair<std::string, int>& p : umap) {  // 注意二者的区别
  //for (const auto& p : umap) {
    std::cout << "address:" << &p << ", first:" << &(p.first) << ", second:" << &(p.second) << std::endl;
  }
}

/*===============================================auto类型推导=========================================*/
const std::string&
foo() {
  auto str = new std::string("foo");
  std::cout << str << std::endl;
  return *str;
}

const std::string
foo2() {
  auto str = "foo";
  std::cout << &str << std::endl;
  return str;
}

std::string
foo3() {
  auto str = new std::string("foo");
  std::cout << str << std::endl;
  return *str;
}

const std::string*
foo4() {
  auto str = new std::string("foo");
  std::cout << str << std::endl;
  return str;
}

std::string*
foo5() {
  auto str = new std::string("foo");
  std::cout << str << std::endl;
  return str;
}

void test2() {  // auto类型推导
  // 返回 const std::string&
  auto str1 = foo();          // std::string
  auto& str11 = foo();        // const std::string&
  const auto& str12 = foo();  // const std::string&
  const auto str13 = foo();   // const std::string

  // 返回 const std::string
  auto str2 = foo2();          // std::string
  auto& str21 = foo2();        // const std::string&
  const auto& str22 = foo2();  // const std::string&
  const auto str23 = foo2();   // const std::string

  // 返回 std::string
  auto str3 = foo3();  // std::string

  // 返回 const std::string*
  auto str4 = foo4();          // const std::string*
  const auto* str41 = foo4();  // const std::string*
  auto* str42 = foo4();        // const std::string*
  const auto str43 = foo4();   // const std::string* const
 
  // 返回 std::string*
  auto str5 = foo5();          // std::string*
  const auto* str51 = foo5();  // const std::string*
  auto* str52 = foo5();        // std::string*
  const auto str53 = foo5();   // std::string* const

  std::cout << "this is in foo." << std::endl;
}

/*===============================================auto陷阱=========================================*/

void foo4(bool x) {
  return;
}

void test3() {  // C++不允许bit级别的引用
  std::vector<bool> boolean_vec {true, false, false, true};
  auto& rbool = boolean_vec;
  auto var1 = boolean_vec[3];  // std::vector<bool>::reference
  bool var2 = boolean_vec[3];  // 隐式类型转换：std::vector<bool>::reference -> bool
  foo4(var1);
  foo4(var2);
  return;
}

int main() {
  test2();

  return 0;
}