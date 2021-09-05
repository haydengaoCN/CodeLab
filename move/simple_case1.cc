#include <iostream>
#include <vector>
#include <memory>

class Widget {
 public:
  Widget() : length_(0), parray_(nullptr) {}
  Widget(size_t length) : length_(length) {
    parray_ = new uint32_t[length_];
    std::cout << "[widget ctor] address of parray:" << parray_ << ", this:" << this << std::endl << std::endl;
  }
  explicit Widget(const std::vector<uint32_t>& vec) {
    if (vec.empty()) return;
    length_ = vec.size();
    parray_ = new uint32_t[length_];
    if (!parray_) return;
    for (auto idx = 0; idx < length_; ++idx) {
      parray_[idx] = vec[idx];
    }
    std::cout << "[widget ctor] address of parray:" << parray_ << ", this:" << this << std::endl << std::endl;
  }
  Widget(size_t len1, uint32_t init_val) {
    if (len1 == 0) return;
    parray_ = new uint32_t[len1];
    for (auto idx = 0; idx < len1; ++idx) {
      parray_[idx] = init_val;
    }
    std::cout << "[widget ctor2] address of parray:" << parray_ << ", this:" << this << std::endl << std::endl;
  }
  Widget(const Widget& w) {
    length_ = w.length_;
    parray_ = new uint32_t[length_];
    if (!parray_) return;
    for (auto idx = 0; idx < length_; ++idx) {
      parray_[idx] = w.parray_[idx];
    }
    std::cout << "[widget copy-ctor] build widget by copy-ctor, address:" << parray_ << ", this:" << this << std::endl << std::endl;
  }
  Widget& operator = (const Widget& w) {
    length_ = w.length_;
    parray_ = new uint32_t[length_];
    if (!parray_) return *this;
    for (auto idx = 0; idx < length_; ++idx) {
      parray_[idx] = w.parray_[idx];
    }
    std::cout << "[widget copy-assignment] build widget by copy-assignment, address:" << parray_ << ", this:" << this << std::endl << std::endl;
    return *this;
  }
  Widget(Widget&& w) {
    length_ = w.length_;
    parray_ = w.parray_;
    std::cout << "[widget move-ctor] build widget using move-ctor, address:" << parray_ << ", this:" << this << std::endl << std::endl;
  }
  Widget& operator = (Widget&& w) {
    length_ = w.length_;
    parray_ = w.parray_;
    std::cout << "[widget move-assignment] build widget using move-assignment, address:" << parray_ << ", this:" << this << std::endl << std::endl;
    return *this;
  }
  ~Widget() {
    if (!parray_) {
      std::cout << "[widget dtor] memory collector:" << parray_ << ", this:" << this << std::endl << std::endl;
      delete[] parray_;
    }
  }
  void ShowArray() const {
    if (length_ == 0 || !parray_) {
      return;
    }
    std::cout << "[widget show-array] display array:" << parray_ << std::endl;
    for (auto idx = 0; idx < length_; ++idx) {
      std::cout << "idx:" << idx << " val:" << parray_[idx] << ", ";
    }
    std::cout << std::endl << std::endl;
  }
  /*
  void* operator new (size_t len) {
    void* p = malloc(sizeof(size_t) + sizeof(uint32_t*));
    std::cout << "[widget custom new] allocated memory address:" << p << std::endl << std::endl;
    return p;
  }
  void operator delete (void* p) {
    std::cout << "[widget custom delete] released  memory address:" << p << std::endl << std::endl;
    if(p) ((Widget*)p)->~Widget();
  }
  static Widget MakeWidget(const std::vector<uint32_t>& in) {
    Widget w(in);
    return std::move(w);
  }
  */
 private:
  size_t length_{0};
  uint32_t* parray_;
};

class Foo {
 public:
  Foo() {}
  explicit Foo(const Widget& pw) {
    pw_ = pw;
  }
 private:
  Widget pw_;
};

void ProcessWidget (Widget w) {
  // do something;
  return;
}
void test() {
  std::vector<uint32_t> vec{1, 2, 3};
  Widget w1(vec);
  Widget w2(w1);

  Foo foo1(w1);
  Foo foo2(w2);
  Foo foo3, foo4;
  foo3 = std::move(foo1);  // 这里不再需要重新构造一个widget给foo3
  foo4 = foo2;  // 这里需要调用widget copy_assignment，重新申请构造一个widget给foo4
}

void test2() {
  std::vector<uint32_t> in{1, 2, 3};
  //std::shared_ptr<Widget> shw(new Widget(in), [](Widget* pw) { if (pw) {std::cout << "[widget custom deleter]" << std::endl; pw->~Widget();}});
  std::shared_ptr<Widget> shw(new Widget(in));
  std::weak_ptr<Widget> wp(shw);
  auto mshw2 = std::make_shared<Widget>(in);
  std::weak_ptr<Widget> mwp(mshw2);

  shw = nullptr;  //  call deleter, release widget
  mshw2 = nullptr;

  wp.reset();
  mwp.reset();
  return;
}


void test3() {
  std::vector<Widget> vec;
  std::cout << "push_back" << std::endl;
  Widget w1({1, 2, 3});
  vec.push_back(w1);
  std::cout << "emplace_back" << std::endl;
  Widget w2({1, 2, 3});
  vec.emplace_back(w2);
  std::cout << "push_back2" << std::endl;
  vec.emplace_back(Widget({1, 2, 3}));
  std::cout << "emplace_back2" << std::endl;
  vec.emplace_back(Widget({1, 2, 3}));
  std::cout << "emplace_back3" << std::endl;
  vec.emplace_back(2, 3);

  for (const auto& item : vec) {
    item.ShowArray();
  }
  return;
}


void test4() {
  std::vector<std::string> vec;

  std::cout << "push_back" << std::endl;
  std::string str1 = "hello";
  vec.push_back(str1);

  std::cout << "emplace_back" << std::endl;
  std::string str2 = "world";
  vec.emplace_back(str2);

  std::cout << "push_back2" << std::endl;
  vec.push_back("hello");

  std::cout << "emplace_back2" << std::endl;
  vec.emplace_back("world");

  return;
}

/*
 The traditional wisdom is that push_back will construct a temporary object,
 which will then get moved into v whereas emplace_back will forward the argument along and construct it directly in place with no copies or moves.
 This may be true based on the code as written in standard libraries.

 emplace_back will call any type of constructor out there, whereas the more cautious push_back will call only constructors that are implicit.
*/
void test5_push() {
  std::vector<Widget> vec;

  std::cout << "push_back1" << std::endl;
  vec.push_back(1);
  std::cout << "push_back2" << std::endl;
  vec.push_back(Widget(2));
  std::cout << "push_back3" << std::endl;
  Widget tmp(3);
  vec.push_back(tmp);
}

void test5_emplace() {
  std::vector<Widget> vec;

  std::cout << "emplace_back1" << std::endl;
  vec.emplace_back(11);
  std::cout << "emplace_back2" << std::endl;
  vec.emplace_back(Widget(12));
  std::cout << "emplace_back3" << std::endl;
  Widget tmp(13);
  vec.emplace_back(tmp);
}

Widget test6() {
  Widget tmp(1);
  return tmp;
}
Widget test7() {
  Widget tmp(1);
  return std::move(tmp);
}

int main() {
  Widget tmp1 = test6();
  std::cout << "tmp1 address:" << &tmp1 << std::endl;
  Widget tmp2 = test7();
  std::cout << "tmp2 address:" << &tmp2 << std::endl;
  return 0;
}
