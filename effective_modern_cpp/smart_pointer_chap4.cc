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

/*
draws of raw pointers:
1 - 6
*/

/*==========================================================ITEM18 unique_ptr==========================================================*/
/*
Item 18: Use std::unique_ptr for exclusive-ownership resource management.
1. std::unique_ptr is a small, fast, move-only smart pointer for managing resources with exclusive-ownership semantics.
2. By default, resource destruction takes place via delete, but custom deleters can be specified.
   Stateful deleters and function pointers as deleters increase the size of std::unique_ptr objects.
   Stateless function objects (e.g., from lambda expressions with no captures) incur no size penalty.
3. Converting a std::unique_ptr to a std::shared_ptr is easy.

自定义delete函数：
By default, that destruction would take place via delete, but, during construction,
std::unique_ptr objects can be configured to use custom deleters: arbitrary functions (or function objects, including those arising from lambda expressions)
to be invoked when it’s time for their resources to be destroyed.

当生命周期结束时，unique_ptr变量会自动调用delete函数销毁所拥有的资源。
std::unique_ptr is thus a move-only type;
非常不推荐使用unique_ptr指向array, vector, string等。
*/

namespace MODERN::ITEM18 {
class Investment;

// use lambda function as deleter
auto delInvmt1 = [](Investment* pInvestment) { /*makeLogEntry(pInvestment)*/; delete pInvestment; };
template<typename... Ts>
std::unique_ptr<Investment, decltype(delInvmt1)>  // return type
MakeInvestment(Ts&&... args);

void delInvmt2(Investment* pInvestment) {
  /*makeLogEntry(pInvestment);*/
  delete pInvestment;
}

// use function pointer
// return type has size of Investment* plus at least size of function pointer!
template<typename... Ts>
std::unique_ptr<Investment, void (*)(Investment*)>  // return type
MakeInvestment2(Ts&&... params);

}  // end namespace MODERN::ITEM18

/*==========================================================Item19 shared_ptr==========================================================*/
/*
Item 19: Use std::shared_ptr for shared-ownership resource management.
Q: 什么时候资源会被释放？
A: shared_ptr记录了指向同一资源的智能指针的count, 当没有share_ptr指向时，资源将得到释放。

Q: 如何计数？
A: 调用shared_ptr的1) ctor +1, 2) dtor -1, 3) copy-assignment do both. 
   move-ctor不增不减，不需要修改reference count; 因此move比copy快，(move-ctor quicker than copy-ctor, move-assign quicker than copy-assign)

1. reference count
  1) std::shared_ptrs are twice the size of a raw pointer;
     one for raw pointer to the resource and another one for the reference count;
  2) Memory for the reference count must be dynamically allocated; 
     the cost of the dynamic allocation is avoided when it's created by std::make_shared;
  3) Increment and decrement of the reference count must be atomic;

2. shared_ptrs pointer to the same resource type with different custom deleter have the same type.
  std::unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel);  // deleter type is part of ptr type
  std::shared_ptr<Widget> spw(new Widget, loggingDel);  // deleter type is not part of ptr type.

3. specifying a custom deleter doesn’t change the size of a std::shared_ptr object.
   Regardless of deleter, a std::shared_ptr object is two pointers in size. 
   two pointers, one is to Object, another is to Control Block. CB includes reference count, weak count and customer deleter, etc.
   unique_ptr has no CB.

4. try to avoid passing raw pointers to a std::shared_ptr constructor.
   if you must pass a raw pointer to a std::shared_ptr constructor, pass the result of new directly instead of going through a raw pointer variable.
   避免emplace_back(this);

5. std::shared_ptr has an API that’s designed only for pointers to single objects. 不要用在array, vector, string等。

std::shared_ptr<T>: ptr to T, ptr to Control Block.
Control Block : Reference Count, Weak Count, Other data (construction, destruction, custom deleter)

Things to Remember
1) std::shared_ptrs offer convenience approaching that of garbage collection for the shared lifetime management of arbitrary resources.
2) Compared to std::unique_ptr, std::shared_ptr objects are typically twice as big, incur overhead for control blocks, and require atomic reference count manipulations.
3) Default resource destruction is via delete, but custom deleters are supported. The type of the deleter has no effect on the type of the std::shared_ptr.
4) Avoid creating std::shared_ptrs from variables of raw pointer type.
*/

namespace MODERN::ITEM19 {
class Widget {
 public:
  uint32_t x{0};
  uint32_t y{0};
};
void test() {
  std::shared_ptr<Widget> sp = std::shared_ptr<Widget>(new Widget);
  std::unique_ptr<Widget> up = std::unique_ptr<Widget>(new Widget);
  return;
}
}  // end namespace MODERN::ITEM19
/*==========================================================ITEM20 weak_ptr==========================================================*/
/*
Item 20: Use std::weak_ptr for std::shared_ptr- like pointers that can dangle.

std::weak_ptr<T>
1) a pointer like std::shared_ptr that doesn’t affect an object’s reference count;
2) std::weak_ptrs are typically created from std::shared_ptrs;
3) std::weak_ptr objects are the same size as std:: shared_ptr objects, they make use of the same control blocks as std:: shared_ptrs.

Things to Remember  什么时候用？
1) Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.
2) Potential use cases for std::weak_ptr include caching, observer lists, and the prevention of std::shared_ptr cycles.
*/

namespace MODERN::ITEM20 {

class Widget {
};

void test() {
  auto spw = std::make_shared<Widget>();  // RC = 1, WRC = 1
  //std::shared_ptr<Widget> spw(new Widget);  // RC = 1, WRC = 1
  std::weak_ptr<Widget> wpw(spw);  // wpw points to same Widget as spw. RC remains 1, WRC +1
  if (wpw.expired()) {  // resource unavailable. can be deteced when dangle.
    return;
  }
  std::shared_ptr<Widget> spw1 = wpw.lock();  // return nullptr if wpw is expired.
  auto spw2 = wpw.lock();
  std::shared_ptr<Widget> spw3(wpw);  // throw std::bad_weak_ptr if wpw is expired.
}

}  // end namespace MODERN::ITEM20

/*==========================================================ITEM21 Prefer std::make_unique and std::make_shared==========================================================*/
/*
ITEM21 Prefer use std::make_unique and std::make_shared to direct use of new.

为什么推荐使用？
1) code duplication should be used.
2) make functions has to do with exception safety.
3) make_shared(including allocated_shared) allows compilers to generate smaller, faster code.
   此时，resource pointer 与 CB pointer不再分来独立申请内存，而是申请一块大的连续的内存；减少了申请的次数，也减少了静态binary的大小；

有些情况下无法使用：
make_shared与make_unique:
1) 无法支持自定义的deleter;
2) braced initializers无法被传入; 

make_shared以下两种情况不建议使用:
1) classes with custom memory management;
   一般而言，自定义的内存分配函数申请的内存大小严格等于class的大小；但是make_shared需要额外申请CB内存.
2) systems with memory concerns, very large objects, and std::weak_ptrs that outlive the corresponding std::shared_ptrs.
   weak_ptr通过RC是否为零来判断resource是否被释放；
   对于shared_ptr, 如果RC为0，则直接释放resource；
   对于make_shared, resource 与 CB 内存是一齐申请的；RC为零，但是WRC不为零，则整块内存将不会释放；
*/

namespace MODERN::ITEM21 {

class Widget {};

std::shared_ptr<Widget> shw(new Widget);
auto shw = std::make_shared<Widget>();  // ()内填的是Wideget的初始化参数，会以()的方式转发到构造函数
std::unique_ptr<Widget> uw(new Widget);
auto uw = std::make_unique<Widget>();

int ComputePriority() {
  return 0;
}

void ProcessWidget(std::shared_ptr<Widget> shw, int priority) {
  return;
}

void test() {
  ProcessWidget(std::shared_ptr<Widget>(new Widget), ComputePriority());  // 三件事：1）new widget, 2) shared_ptr认领，3）ComputePriority
  ProcessWidget(std::make_shared<Widget>(), ComputePriority());  // 两件事：1) make widget; 2) ComputePriority
}

auto up = std::make_unique<std::vector<int>>(10, 20);  // 则将创建一个size10,value全为20的vector智能指针；
auto in = {1, 2, 3};
auto up2 = std::make_unique<std::vector<int>>(in);  //  此时能正确传入braced initializer 

}  // end namespace MODERN::ITEM21
/*==========================================================main==========================================================*/
int main() {
  MODERN::ITEM20::test();
  return 0;
}