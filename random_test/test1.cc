#include <time.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
  using namespace std::chrono_literals;
  time_t tmp0 = time(nullptr);
  std::this_thread::sleep_for(2s);
  int delta = time(nullptr) - tmp0;
  std::cout << delta << std::endl;
  return 0;
}
