#include <iostream>
#include <string>
#include <optional>
#include <variant>

#include <cassert>

namespace optional_space {

std::optional<std::string> create(bool b) {
  //return b ? "Godzilla" : {};
  if (b) {
    return "Godzilla";
  }
  return {};
}

auto create2(bool b) {
  return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}

auto create_ref(bool b) {
  static std::string monster{"Godzilla"};
  return b ? std::optional<std::reference_wrapper<std::string>>{monster} : std::nullopt;
}

void test() {
  std::cout << create(false).value_or("empty") << std::endl;

  if (auto str = create2(true)) {
    std::cout << *str << std::endl;
  }

  if (auto str = create_ref(true)) {
    std::cout << str->get() << std::endl;
    str->get() = "Mothra";
    std::cout << str->get() << std::endl;
  }
}

}  // namespace optional_space

namespace variant_space {

/* variant : a type-safe union
  An instance of std::variant at any given time either holds a value of one of its alternative types, or in the case of error - no value

  union 只允许放置POD数据类型，只允许在本地直接放置(allocated directly)；比如std::string就不能直接放在union内；
*/

void test() {
  std::variant<int, float, std::string> v, w;
  v = 42;  // int
  int value = std::get<int>(v);
  assert(value == 42);

  w = std::get<int>(v);
  //w = std::get<float>(v);  // exception
  //w = std::get<std::string>(v);
  w = std::get<0>(v);
  //w = std::get<1>(v);
  //w = std::get<2>(v);
  w = v;

  try {
    std::get<float>(w); // w contains int, not float: will throw
  }
  catch (const std::bad_variant_access& e) {
    std::cout << e.what() << std::endl;
  }

  using namespace std::literals;
  std::variant<std::string> x("abc");
  x = "def";  // unambiguous
  std::variant<std::string, void const*> y("abc");
  assert(std::holds_alternative<void const*>(y));
  std::cout << y.index() << std::endl;
  y = "xyz"s;
  assert(std::holds_alternative<std::string>(y));
  std::cout << y.index() << std::endl;
}

}  // namespace optional_space

int main() {
  optional_space::test();
  variant_space::test();

  return 0;
}