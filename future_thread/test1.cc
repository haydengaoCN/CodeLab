#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <utility>
#include <future>

namespace scoped_thread {

class scoped_thread {
 public:
  template <typename... Args>
  scoped_thread(Args&&... args) : thread_(std::forward<Args>(args)...) {}
  ~scoped_thread() {
    if (thread_.joinable()) {  // 已经joined或者detach的或者空线程对象都不能join 否则会引发异常
      thread_.join();
    }
  } 
  scoped_thread(const scoped_thread&) = delete;
  scoped_thread(scoped_thread&& scp_thread) : thread_(std::move(scp_thread.thread_)) {}

 private:
  std::thread thread_;
};

void test() {
  std::mutex os_lock;
  scoped_thread t1([&os_lock](){
      std::lock_guard scplock(os_lock);
      using namespace std::literals::chrono_literals;
      std::this_thread::sleep_for(200ms);
      std::cout << "this is thread A" << std::endl; });
  scoped_thread t2([&os_lock](){
      std::lock_guard scplock(os_lock);
      using namespace std::literals::chrono_literals;
      std::this_thread::sleep_for(200ms);
      std::cout << "this is thread B" << std::endl; });
}

}  // namespace scoped_thread


namespace condition_variable {

using scoped_thread = scoped_thread::scoped_thread;
void work(std::condition_variable& cv, int& result) {
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(2s);
  result = 42;
  cv.notify_one();
}

void test() {
  std::condition_variable cv;
  std::mutex cv_mut;
  int result;

  scoped_thread t{work, std::ref(cv), std::ref(result)};

  std::unique_lock lock(cv_mut);
  cv.wait(lock);
  std::cout << "the answer is:" << result << std::endl;
}

}  // conditional_variable

namespace promising_future {

using scoped_thread = scoped_thread::scoped_thread;
int work() {
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(2s);
  return 42;
}

void test() {
  auto fut = async(std::launch::async, work);  // launch::async 是运行策略，交代编译器一定要另起一个线程执行；返回值是std::future<auto>，会自动推导

  std::cout << "waiting now..." << std::endl;
  std::cout << "the answer is:" << fut.get();  // get只能被调用一次，第二次undefine behavior
  std::cout << "exit now." << std::endl;  // get会阻塞当前线程
}

void test2() {
  // 一组promise和future成对出现，既不能重复设，也不可重复取；
  std::promise<int> prom;
  auto fut = prom.get_future();

  scoped_thread t([](std::promise<int> prom){ prom.set_value(42); }, std::move(prom));

  std::cout << "waiting now..." << std::endl;
  std::cout << "the answer is:" << fut.get();  // get只能被调用一次，第二次undefine behavior
  std::cout << "exit now." << std::endl;
}

void test3() {
  std::packaged_task<int()> task{[](){ return 42; }};
  auto fut = task.get_future();
  scoped_thread t(std::move(task));
  
  std::cout << "the answer is:" << fut.get() << std::endl;
}

}

int main() {
  scoped_thread::test();
  condition_variable::test();
  promising_future::test();
  promising_future::test2();
  promising_future::test3();

  return 0;
}