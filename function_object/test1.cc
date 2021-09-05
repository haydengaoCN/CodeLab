#include <iostream>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace function_object {

/* 函数对象(funtion object) / 仿函数(functor)
函数对象：一个可以被当作函数来用的对象。
本质上是对操作符'()'的重载；
*/

struct adder {
  adder(int n) : n_(n) {}
  int operator()(int x) const  {
    return x + n_;
  }

 private:
  int n_ = 0;
};

void test() {
  adder add_by_2(2);
  std::cout << add_by_2(40) << std::endl;
}

}  // namespace fucntion_object

namespace lambda_expr {

/* lambda
完整形式：
  [params1](params2) -> return_type {}
  params1表示捕获的变量；
  params2表示传入的变量；
  返回的类型一般可以省略；

变量捕获：
  '=' 按值捕获，一般而言较为安全；
  '&' 按引用捕获，必须确保被捕获的变量和lambda表达式的生命期至少一样长；

泛型lambda表达式：
  lambda表达式的参数可以声明为auto，相当于模板函数；
  auto sum = [](auto x, auto y) {
    return x + y;
  };
  auto foo = [](auto&&) {};

fuction模板：
  用于承接函数对象，但是比较耗资源；

*/

class task {
 public:
  task(int data) : data_(data) {}
  auto lazy_launch() {
    return [*this, count = get_count()]() mutable {  // 关键字使得可以修改捕获的内容;
      std::ostringstream oss;
      oss << "No." << count << ", work:" << data_ << ", in thread:" << std::this_thread::get_id()
          << std::endl;
      msg_ = oss.str();
      using namespace std::literals::chrono_literals;
      std::this_thread::sleep_for(100ms);
      std::cout << msg_;
    };
  }

 private:
  int get_count() {
    static int count_ = 0;
    return ++count_;
  }
  int data_ = 0;
  std::string msg_;
};

void test() {
  // task t(37);
  task t{37};
  std::thread t1(t.lazy_launch());
  std::thread t2(t.lazy_launch());
  t1.join();
  t2.join();
}

void test2() {
  auto foo = [](auto&&) {};
  int x = 0;
  std::string str1;
  foo(x);
  foo(str1);
}

void test3() {  // function模板
  std::function<int(int, int)> fun = [](int x, int y) { return x + y;};
  auto foo = [](int x, int y) { return x + y;};

  std::cout << fun(3, 4) << std::endl;
  std::cout << foo(3, 4) << std::endl;
}

}  // namespace lambda_expr

int main() {
  function_object::test();
  lambda_expr::test();
  lambda_expr::test2();
  lambda_expr::test3();

  return 0;
}
