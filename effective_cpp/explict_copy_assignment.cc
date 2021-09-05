#include <iostream>

/*====================explicit===========================*/
/*
 if a class has a constructor which can be called with a single argument,
 then this constructor becomes conversion constructor
 because such a constructor allows conversion of the single argument to the class being constructed.
*/
class A {
 public:
  A(int x, int y = 0) {}
};
class B {
 public:
  explicit B(int x) {}
};

void DoSomethingA(A obj) {} 
void DoSomethingB(B obj) {} 
void TestExplict() {
  A obj0_A(2);
  A obj1_A = 3;  // 隐式类型转换
  DoSomethingA(4);
  DoSomethingA(A(5));

  B obj0_B(2);
  //B obj1_B = 3;  // not allowed
  //DoSomethingB(4);  // not allowed
  DoSomethingB(B(5));
}

/*====================copy&assignment===========================*/
/*
1. 新对象被创建，会调用copy-constructor函数；
2. 已经创建的对象之间的赋值，会调用copy-assignment函数；
*/
class Widget {
 public:
  Widget (int x = 0, int y = 0) {
    std::cout << "this is in constructor" << std::endl;
  }

  Widget (const Widget& rhs) {  // copy-constructor
    std::cout << "this is in copy-constructor" << std::endl;
    x = rhs.x;
    y = rhs.y;
  }

  Widget& operator =(const Widget& rhs) { // copy-assignment
    std::cout << "this is in copy-assignment" << std::endl;
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

 private:
  int x;
  int y;
};

void DoSomethingWidget(Widget w) {}

void TestCopyAssign() {
  Widget obj0_W;
  Widget obj1_W = obj0_W;  // call copy-constructor
  Widget obj2_W(obj0_W);  // call copy-constructor
  DoSomethingWidget(obj0_W);
  obj2_W = obj0_W;  // 没有新对象被创建，调用copy-assignment
}


/*=====================const===========================*/
class Rational {
 public:
  Rational(double val = 1.0) {}
  Rational(const Rational&) {
    std::cout << "this is in Rational Copy Constructor." << std::endl;
  }
  Rational operator *(const Rational& rhs) {
    return x * rhs.x;
  }
 private:
  double x;
};

void TestConst() {
  Rational a,b,c;
  a * b = c;
}


int main() {
  TestExplict();

  TestCopyAssign();

  return 0;
}