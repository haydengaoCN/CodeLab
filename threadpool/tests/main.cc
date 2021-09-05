// date: 20210204
// author: haydengao
// describe: for the time of touching fish

#include "threadpool/src/thread_pool.h"

void func() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rand() % 1000));
  std::cout << getpid() << std::endl;
}
int main() {
  std::cout << "main thread:" << getpid() << std::endl;
  size_t tp_size = 4;
  ThreadPool tp(tp_size);
  tp.Init();

  for (auto idx = 0; idx < tp_size; ++idx) {
    tp.submit([]() { std::cout << getpid() << std::endl;});
    // tp.submit(func);
  }

  tp.ShutDown();
  
  return 0;
}