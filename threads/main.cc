#include <thread>
#include <iostream>
#include <unistd.h>

void foo() {
  std::thread run([](){while(1);});
}

int main() {
  while(1) {
    //std::this_thread::sleep_for(1);
    //sleep(1);
    //break;
  }

  return 0;
}
