#include <thread>
#include <iostream>
#include <vector>

void work (int n) {
  std::cout << "this is in thread:" << n << std::endl;
  while(1);
}
class Foo {
 public:
  ~Foo() {
    for (auto& th : tp) {
      if (th.joinable()) {
        th.join();
      }
    }
  }
  void start_threads() {
    tp.emplace_back(std::thread(work, 1));
    tp.emplace_back(std::thread(work, 2));
  }
  
private:
 std::vector<std::thread> tp;
};
int main() {
  std::vector<int> vec;
  // vec[0] = 100;

  Foo foo;
  foo.start_threads();

  while(1);
  return 0;
}
