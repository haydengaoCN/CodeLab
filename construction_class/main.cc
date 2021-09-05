#include <iostream>
#include <string>
#include <unordered_map>

struct Foo {
  Foo () = default;
  Foo (const std::string& key, const std::string& val) : key_(key), val_(val) {}

  std::string key_, val_;
};

int main() {
  std::unordered_map<int ,Foo> umap;
  std::cout << umap.count(0) << std::endl;
  return 0;
}
