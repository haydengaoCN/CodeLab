#include <iostream>

class base {
 public:
  base(int* x = nullptr) : iptr(x) {}
  virtual ~base() {
    std::cout << "this is in base destruction." << std::endl;
    delete iptr;
  }
  int* iptr;
};

class deri : public base {
 public:
  deri(int* x, int* y) {
    iptr = x;
    iptr2 = y;
  }
  ~deri() {
    std::cout << "this is in deri destruction." << std::endl;
    // delete iptr;
    delete iptr2;
  }
  int* iptr2;
};

void test() {
  int* px = (int*)malloc(sizeof(int));
  int* py = (int*)malloc(sizeof(int));
  *px = 0;
  *py = 1;

  deri insderi = deri(px, py);
  base* pbase = &insderi;

}

base* f3() {
  base* ret = (base*)malloc(sizeof(base));
  return ret;
}
int main() {
  // test();
  std::cout << f3()->iptr << std::endl;

  return 0;
}
