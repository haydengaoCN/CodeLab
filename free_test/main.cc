/*
tasks.json (compiler build settings)
launch.json (debugger settings)
c_cpp_properties.json (compiler path and IntelliSense settings)

ref: https://code.visualstudio.com/docs/cpp/config-clang-mac
*/
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Foo {
 public:
  Foo() {
    std::cout << "string address:" << &wonder_str << std::endl;
  }
  std::string wonder_str;
};

Foo* FooFactory() {
  Foo* foo = new Foo;
  return foo;  
}

int main() {
    Foo* foo = FooFactory();

    return 0;
}