#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <unordered_map>
#include <list>
#include <mutex>
#include <atomic>
#include <math.h>

#if 0
/*==========================================================Item7 () vs. {}==========================================================*/
/*
item7: distinguish between () and {} when creating objects.
  1. distinguish initialization from assignment;
     Widget w1;  // call default constructor;
     Widget w2 = w1;  // call copy ctor;
     w1 = w2;  // call assignment, copy operator=
  2. Braced initialization is introduced as uniform initialization by C++11.
*/

/*
{} 作为uniform initialization
1) 可以用于任意变量的初始化；
2）prohibiting implicit narrowing conver‐ sions among built-in types.
3) 避免vexing parse 
   Widget w2();  // 声明了一个函数？
   Widget w2{};  // cal default ctor.

但是仍会存在一些问题:braced initializers vs. std::initializer_lists vs. constructor overload resolution.
1）calls using the braced initialization syntax strongly prefer the overloads taking std::initializer_lists.
   注意，类里面存在用initializer_lists作为初始化参数的初始化函数，可能会被错误的调用。
   std::vector<int> v1(10, 20);  // v1 size 10, all elements are 20
   std::vector<int> v2{10, 20};  // v1 has two elements, 10, 20
2）Only if there’s no way to convert the types of the arguments in a braced initializer to the type in a std::initializer_list
   do compilers fall back on normal overload resolution
3) Empty braces mean no arguments, not an empty std::initializer_list;
*/
class Foo {
 public:
  Foo() {};
  Foo(int x, int y) : _x(x), _y(y) {}
  Foo(int x, int y, int z) : _x(x), _y(y), _z(z) {}

 private:
  int _x{0};
  int _y = 0;
  int _z = 0;
  std::vector<int> _v{0, 1, 2};
};
void test1() {
  int x{0};
  std::vector<int> vecx{1, 2, 3};
  double a, b ,c;
  int sum1 = a + b + c;  // it's ok
  int sum2(a + b + c);  // ditto
  int sum3{a + b + c};  // not allowed, warnning!

  Foo foo;
  Foo foo2{0, 1};
  Foo foo3{0, 1, 2};
}

/*==========================================================Item8 Prefer nullptr==========================================================*/
/*
  1. NULL and 0 have no pointer type. It'll grudgingly interpret 0 and NULL as a null pointer.
  2. nullptr acts as if it were a pointer of all types and can't be viewed as anything integral.
     std::nullptr_t
    
  summary:
    1. Prefer nullptr to and NULL;
    2. Avoid overloading on integral and pointer types.
*/
namespace MODERN::ITEM8 {

class Widget {

};

void f1(std::shared_ptr<Widget> spw) {

}

void f2(std::unique_ptr<Widget> upw) {

}

void f3(Widget* pw) {

}

// more complicated case
template<typename FuncType, typename PtrType>
void FuncProxy(FuncType func, PtrType ptr) {
  func(ptr);
}
void test() {
  // below is OK.
  f1(0);
  f2(0);
  f3(0);
  f1(NULL);
  f2(NULL);
  f3(NULL);
  f1(nullptr);
  f2(nullptr);
  f3(nullptr);

  // 第一层模板匹配将0或者NULL转化为整型，到func层次无法将整型转化为指针
  // FuncProxy(f1, 0);
  // FuncProxy(f2, NULL);
  // FuncProxy(f3, 0);

  // below is ok
  FuncProxy(f1, nullptr);
  FuncProxy(f2, nullptr);
  FuncProxy(f3, nullptr);
}

}  // end namespace MODERN::ITEM8

/*==========================================================Item8 Prefer alias declarations to typedefs==========================================================*/
/*
summary:
  1) typedefs don't support templatization, but alias declarations do.
*/
namespace MODERN::ITEM9 {

class Widget{};

typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;
using UPtrMapSS2 = std::unique_ptr<std::unordered_map<std::string, std::string>>;

typedef void (*FP)(int, const std::string&);
using FP2 = void (*)(int, const std::string&);

// 模板别名
// alias 更加简洁
template<typename T>
using MyAllocList = std::list<T/*, MyAlloc<T>*/>;
MyAllocList<Widget> lw;

template<typename T>
struct MyAllocList2 {
  typedef std::list<T/*, MyAlloc<T>*/> type;
};
MyAllocList2<Widget>::type lw2;

// 奇怪的知识点
// std::remove_const<T>::type;         // yields T from const T
// std::remove_reference<T>::type      // yields T from T& and T&&
// std::add_lvalue_reference<T>::type  // yields T& from T

// in C++14
template<class T>
using remove_const_t = typename std::remove_const<T>::type;

void foo(std::string val) {}
void foo2(const std::string val) {}
void foo3(std::string* val) {}

void test(const std::string* pin,
          const std::string& rin) {
  foo(rin);
  foo3(remove_const_t<std::string*>(pin));
}
}  // end namespace MODERN::ITEM9


/*==========================================================Item10 Prefer Scoped enums to unscoped enums==========================================================*/
/*
  every enum in C++ has an integral underlying type that is determined by compilers. 
  size and speed are two important factors.
  
  unscoped enum : enum Color
  scoped enum   : enum class Color
    1) no namespace pollution;
    2) enumerators for unscoped enums implicitly convert to integral types;
    3) scoped enums can be forward-declared while unscoped enums need additional specification;
*/
namespace MODERN::ITEM10 {
void foo() {
  // enum变量发生了泄漏，花括号外面的环境不允许使用和Color1中enum变量相同的名称。
  enum Color1 {black, white, red};
  enum class Color2 {black, purple, red};

  // auto white = false;  // it's not ok.
  auto purple = false; // it's ok
  // Color2 c = red;  // error! no variables named red out of Color2

  Color1 c1 = Color1::white;
  Color2 c2 = Color2::purple;
  
  if (c1 < 10.1) {
    std::cout << "unscoped enum can be implictly convert to intergral types" << std::endl;
  //} else if (c2 < 20.1) {  // not ok
  } else if (static_cast<double>(c2) < 20.1) {  // not ok
    std::cout << "scoped enum can't be convert to intergral types" << std::endl;
  }

  // enum Color3;  // error!
  enum Color3 : std::uint32_t;  // ok

  enum class Color4;  // ok
  enum class Color5 : std::uint32_t;  // ok
}
}  // end namespace MODERN::ITEM10
/*==========================================================ITEM11 Prefer Deleted Functions==========================================================*/
/*
Item 11: Prefer deleted functions to private undefined ones. 主要讨论如何优雅的禁止函数被调用
1）declare those function private and try not to define them.
   Outside callers can't call these functions while members functions will failed in link when trying calling them.
2) declare functions public and use delete;
   public will produce clearer error infos.
*/
namespace MODERN::ITEM11{
class Foo {
 public:
  Foo();
  Foo(Foo& foo) = delete;  //  deleted function
 private:
  Foo& operator = (Foo& foo);  // not define
};

// 设法阻止变量通过隐式变换调用函数
bool isLucky(int num);  // can also be called by bool, double, float, bool
bool isLucky(double num) = delete;  // forbid both double and float
bool isLucky(bool num) = delete;  // forbid bool

// 设法阻止某些类型实例化模板函数
template<typename T>
void ProcessPointer(T* ptr){}

template<>
void ProcessPointer(char* ptr) = delete;

template<>
void ProcessPointer(const char* ptr) = delete;

template<>
void ProcessPointer(void* ptr) = delete;

template<>
void ProcessPointer(const void* ptr) = delete;

class Boo{
 public:
  Boo();

  template<typename T>
  void IsAlive(T* in);

  // explict instantiation is not allowed inside class;
/*
  template<>
  void IsAlive(void* in) = delete;
*/
};

template<>
void Boo::IsAlive(void* in) = delete;

}  // end namespace MODERN::ITEM11
/*==========================================================ITEM12 override==========================================================*/
/*
Item 12: Declare overriding functions override.  override关键字可以在编译阶段检查虚函数是否写的合法
1. C++11语法：函数的引用性，&， &&
2. 虚函数规范：
3. override能够帮忙检查虚函数是否合法；
4. final keywords:
   Applying final to a virtual function prevents the function from being overridden in derived classes.
   final may also be applied to a class, in which case the class is prohibited from being used as a base class.

Things to remember:
  1) Declare overriding functions override;
  2) Member function reference qualifiers make it possible to treat lvalues and rvalue objects differently.
*/
namespace MODERN::ITEM12 {
// 函数的引用性
class Widget {
 public:
  using DataType = std::vector<double>;
  DataType& data() & {
    return values;
  }
  DataType data() && {
    return std::move(values);
  }

 private:
  DataType values;
};

Widget WidgetFactory() {
  Widget w;
  return w;
}

void test() {
  Widget w;
  auto vals1 = w.data();  // calls lvalue overload for Widget::data, copy-constructs vals1;
  auto vals2 = WidgetFactory().data();  // calls rvalue overload for Widget::data, move constructs vals2;
}

// accept only lvalue Widgets
void DoSometing(Widget& w);
// accept only rvalue Widgets
void DoSomething(Widget&& w);
// accept both
void DoSomething(const Widget& w);

/*
overriding requirements:
  1) The base class must be virtual;
  2) The base and derived function names must be identical(except in the case of destructors);
  3) The parameters types of the base and derived functions must be identical;
  4) The constness of base and derived functions must be identical;
  5) The return types and exception specifications of the base abd derived functions must be compatible;
  6) The functions' reference qualifiers must be identical;
*/

/*
overriding will help check these requirements.
compilers will complaint if requirements disobeyed.
*/
class Base {
 public:
  virtual void mf1() const;
  virtual void mf2(int x);
  virtual void mf3() &;
  virtual void mf4() const;
};

class Derived: public Base {
 public:
  virtual void mf1() const override;
  virtual void mf2(int x) override;
  virtual void mf3() & override;
  void mf4() const override;
};

}  // end namespace MODERN::ITEM12
/*==========================================================ITEM13 Prefer const_iters==========================================================*/
/*
Item13 Prefer const_iterators to iterators.
1. const_iterators are the STL equivalent of pointers-to-const. They point to values that may not be modified.
   The container member functions cbegin and cend produce const_iterators;
2. C++11 added the non-member functions begin and end, but it failed to add cbegin, cend, rbegin, rend, crbegin, and crend.
   C++14 rectifies that oversight.
3. Invoking the non-member begin function (provided by C++11) on a const container yields a const_iterator.

Things to remerbers:
  1) Prefer const_iterators to iterators.
  2) In maximally generic code, prefer non-member versions of begin, end, rbegin, etc., over their member function counterparts.
*/
namespace MODERN::ITEM13 {
  template<typename T>
  auto cbegin(const T& container) -> decltype(std::begin(container)) {  // C++11 style
    return std::begin(container);  // const container return const iters
  }

  void test() {
    const std::vector<std::string> cvec{"one", "two", "three"};
    auto val = cvec[0];
    auto iter1 = cvec.begin();  // const_iterator
    auto iter2 = std::begin(cvec);  // const_iterator

    const std::unordered_map<std::string, uint32_t> umap { {"one", 1}, {"two", 2}};
    // auto val2 = umap["one"];  // illegal
    auto val3 = umap.at("one");  // fine
  }
}  // end namespace MODERN::ITEM13
/*==========================================================ITEM14 Declare functions noexcept when necessary==========================================================*/
/*
Item 14: Declare functions noexcept if they won’t emit exceptions.

Things to Remember
  1) noexcept is part of a function’s interface, and that means that callers may depend on it.
  2) noexcept functions are more optimizable than non-noexcept functions.
  3) noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.
  4) Most functions are exception-neutral rather than noexcept.

RetType function(params) noexcept;  // most optimizable  C++11 style
RetType function(params) throw();   // less optimizable  C++98 style
RetType function(params);           // less optimizable

*/
/*==========================================================ITEM15 Use constexpr whenever possible==========================================================*/
/*
1. constexpr objects have values known at compile time. They maybe placed in read-only memory.
   const objects need not be initialized with values known during compilation.
   all constexpr objects are const, but not all const objects are con stexpr.
2. constexpr functions produce compile-time constants when they are called with compile-time constants.
   If they’re called with values not known until runtime, they produce runtime values.
   * constexpr functions can be used in contexts that demand compile-time constants. 
     If the values of the arguments you pass to a constexpr function in such a context are known during compilation, the result will be computed during compilation.
     If any of the arguments’ values is not known during compilation, your code will be rejected.
   * When a constexpr function is called with one or more values that are not known during compilation, it acts like a normal function, computing its result at runtime.

Things to Remember
1) constexpr objects are const and are initialized with values known during compilation.
2) constexpr functions can produce compile-time results when called with arguments whose values are known during compilation.
3) constexpr objects and functions may be used in a wider range of contexts than non-constexpr objects and functions.
4) constexpr is part of an object’s or function’s interface.
*/
namespace MODERN::ITEM15 {
int sz;
const auto array_size = sz;  // fine  const copy of sz.
// constexpr auto array_size = sz;  // error!
constexpr auto kArraySize = 10;  // fine
// std::array<int, sz> data1;//  error!
std::array<int, kArraySize> data2;  // fine

// how to write constexpr functions
constexpr int pow(int base, int exp) noexcept {  // C++11 style
  return (exp == 0 ? 1 : base * pow(base, exp - 1));
}

constexpr int pow2(int base, int exp) noexcept {  // C++14 style
  auto result = 1;
  for (int i = 0; i < exp; ++i) result *= base;
  return result;
}

}  // end namespace MODERN::ITEM15
/*==========================================================ITEM16 Make const member functions thread safe==========================================================*/
/*
1. const member functions 是在告诉clients这个函数是只读的；这意味着多个线程可以同时调用这个函数；
   因此，需要保证线程安全。
2. 线程安全：加锁 or 原子操作

Things to Remember
1) Make const member functions thread safe unless you’re certain they’ll never be used in a concurrent context.
2) Use of std::atomic variables may offer better performance than a mutex, but they’re suited for manipulation of only a single variable or memory location.
*/
namespace MODERN::ITEM16 {
class Point {
 public:
  double distanceFromOrigin() const noexcept {
    ++call_count;
    return std::sqrt((x * x) + (y * y));
  }
 private:
  mutable std::atomic<unsigned int> call_count{0};
  double x, y;
};

class Widget {
 public:
  int magicValue() const {
    std::lock_guard<std::mutex> guard(m);
    if (cacheValid) {
      return cachedValue;
    } else {
      auto val1 = ExpensiveComputation1();
      auto val2 = ExpensiveComputation2();
      cachedValue = val1 + val2;
      cacheValid = true;
      return cachedValue;
   }
 }

 private:
  int ExpensiveComputation1() const{
    return 0;
  }
  int ExpensiveComputation2() const {
    return 0;
  }
  mutable std::mutex m;  // 这里必须使用加锁，保证只有一个线程进入复杂的计算
  mutable int cachedValue;
  mutable bool cacheValid{ false };
};

}  // end namespace MODERN::ITEM16
#endif
/*==========================================================ITEM17 Understand special member function generation==========================================================*/
/*
1. 编译器有条件的自动生成六个特殊成员函数；
2. 生成条件:
  2.1 move operations, 包括move-ctor and move-assignment，默认以member-wise的方式move非静态成员变量;
      需要满足以下几个条件:
      1) No copy operations are declared in the class; (如果拷贝函数需要自定义，说明一般的member-wise move会出问题)
      2) No move operations are declared in the class; (如果显示定义了其中一个，另外一个不会自动生成，理由ditto)
      3) No destructors is declared in the class;  (说明涉及到复杂的内存处理，ditto)
  2.2 copy-ctor，默认生成需要满足以下几个条件:
      1) No copy-ctor is declared in the class;  (如果developer自定义了copy-ctor, 编译器自然不会生成默认的)
      2) No move operations are declared in the class;  (move operations 无法自动生成，说明涉及到了复杂内存处理)
  2.3 copy-assignment, 默认生成需要满足以下几个条件：
      1) No copy-assignment is declared in the class;
      2) No move operations are declared in the class;
  2.4 default constructor, 也就是不带参数的构造函数，默认生成条件：没有显式声明任何构造函数ctor;
      1) No copy-ctor is declared in the class;
      2) No move-ctor is declared in the class;
      3) No any ctor with or without parameters;
  几点解释：
  1) copy-ctor 与 copy-assignment 是互相独立的，显式定义其中一个并不会影响另一个的默认生成；
  2) move-ctor 与 move-assignment 是depedent，任一被定义将阻止另外一个的自动生成；
     move operations 如果未定义但还是被调用了，则将会调用copy operations;
  3) 显式的定义析构函数将会阻止move operations的默认生成，但是并不会影响copy operations;
  4) Member function templates never suppress generation of special member functions;
  5）如果这六个函数(之一)被阻止自动生成了，但是恰好自动生成的函数能够满足要求，那么关键字default helps.
3. The Rule of Three.
  If you declare any of a copy constructor, copy assignment operator, or destructor, you should declare all three.
  如果你需要自定义以上三者之一的话，说明涉及到了复杂的内存操作，默认生成的成员函数可能无法胜任，因此建议全部自己生成。
*/


// ITEM17 example code
namespace MODERN::ITEM17 {
// 满足一定条件下，编译器会自动生成以下六个特殊的成员函数
class Widget {
  Widget();  // default constructor;
  ~Widget();  // destructor;
  Widget(const Widget& w);  // copy constructor;
  Widget& operator = (const Widget& w);  // assignment operator
  Widget(Widget&& rhs);  // move constructor, no need add const qualifier given this design.
  Widget& operator = (Widget&& rhs);  // move assignment operator, no need add const qualifier given this design.
};

class Foo {
 public:
  Foo() {}
  ~Foo() {}  // move operations is deleted
  Foo(Foo&&) = default;  // explicitly declare it.
  Foo& operator = (Foo&&) = default;
};

void test() {
  Foo foo1, foo2;
  Foo foo3(std::move(foo1));
  foo3 = std::move(foo2);
}


}  // end namespace MODERN::ITEM17
/*==========================================================main==========================================================*/
int main() {
  MODERN::ITEM17::test();

  return 0;
}