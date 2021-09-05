#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace WEEK1 {
/*
  1. why string_view?
  1) std::string to const char* need to use c_str() function, efficient but inconvenient!
  2) const char* to std::string doesn't need do anyting additional but will invoke the creation of a temporary string.
  3) 总的来说，就是std::string_view能够高效的接受这两种类型的参数，不需要拷贝或者显示的进行转换.

  2. string_view feature:
  1) a pointer with a length => a shallow operation;
  2) 无法修改string_view的指针所指向的内容；

  3. when use?
  1) 如果需要一个string的引用，并且不修改内部内容。

  4. additional notes:
  1) passing string_view by value;
  2) underlying data will outlives the string_view; 必须保证string_view依赖的数据活得比string_view长.

*/
  void ProcessedStringView(std::string_view sv) {
    std::cout << sv << std::endl;
  }
  void ProcessedString(const std::string& str) {
    std::cout << str << std::endl;
  }
  void ProcessedCharPoint(const char* pchar) {
    std::cout << pchar << std::endl;
  }

  void test() {
    const char* pchar = "const char*";  // const char* end with NULL
    const std::string str = "const std::string";
    std::string_view sv1(pchar);
    std::string_view sv2(str);

    ProcessedStringView(pchar);
    ProcessedStringView(str);
    ProcessedStringView(sv1);
    ProcessedStringView(sv2);

    ProcessedString(pchar);  // make a copy
    ProcessedCharPoint(str.c_str());  // explicit conversion

    // printf("%s\n", sv.data()); // not safe
  }
  
  void test2() {  // 万物皆可string_view
    std::vector<uint32_t> vec_data{1, 2, 3};
    
    char* pchar_data = reinterpret_cast<char*>(vec_data.data());  // 这里需要进行强制类型转换
    auto  len_char = vec_data.size() * sizeof(uint32_t);  // 统一转换为char, 也就是以字节为单位
    std::string_view sv(pchar_data, len_char);
    
    const uint32_t* p_data = (uint32_t*)(sv.data());
    auto len_data = sv.size() / sizeof(uint32_t);
    for (auto idx = 0; idx < len_data; ++idx) {
      std::cout << "idx: " << p_data[idx] << ", ";
    }
    std::cout << std::endl;

/*
    auto sh_data = std::make_shared<uint32_t>();  // 这里会导致内存释放两次
    sh_data.reset((uint32_t*)sv.data());
    // auto sh_data = std::shared_ptr<uint32_t>((uint32_t*)sv.data());
    for (auto idx = 0; idx < len_data; ++idx) {
      std::cout << "idx: " << p_data[idx] << ", ";
    }
    std::cout << std::endl;
*/
  }

  class Foo {
   public:
    Foo() {
      std::cout << "[Foo ctor]" << std::endl;
    }
    ~Foo() {
      std::cout << "[Foo dtor]" << std::endl;
    }
   
  };
  void test3() {
    auto shptr = std::make_shared<Foo>();
  }
}  // end namespace WEEK1

int main() {
  WEEK1::test();
  WEEK1::test2();
  WEEK1::test3();

  return 0;
}
