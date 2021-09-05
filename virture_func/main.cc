#include <iostream>
class base {
  public:
    base () {};
    virtual void print (int x) {
      std::cout << "int " << x << std::endl;
      std::cout << "this is in base" << std::endl;
      print_privacy();
    }
    virtual void print_privacy () {
      std::cout << "privacy == " << privacy << std::endl;
    }
  private:
    double privacy = 0;;
};
class deri : public base {
  public:
    deri() {}
    /*
    void print (int  x) {
      std::cout << "x = " << x << std::endl;
      std::cout << "this is in deri" << std::endl;
    }*/
    void AccessPrivacy () {
      std::cout << privacy2 << std::endl;
    }
    virtual void print_privacy () {
      std::cout << "privacy == " << privacy2 << std::endl;
    }
  private:
    double privacy2 = 1;
};
int main() {
  deri d;
  base* pbase = &d;
  int i_num = 0;
  double d_num = 0.0;
  pbase->print(i_num);
  //d.AccessPrivacy();
  return 0;
}
