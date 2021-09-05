#include <iostream>
#include <string>
#include <map>
#include <vector>

void Foo(std::vector<std::map<std::string, std::string>*> m) {}
int main() {
  std::map<std::string, std::string> m{
      {"1", "one"}, {"2", "two"}};
  Foo({&m});
  return 0;
}
