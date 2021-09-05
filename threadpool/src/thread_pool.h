// date: 20210204
// author: haydengao
// describe: for the time of touching fish

#pragma once

#include <unistd.h>

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <future>

#include "threadpool/src/safe_queue.h"

class ThreadPool {
 public:
  ThreadPool(size_t thread_pool_size) : tp_size_(thread_pool_size) {
    tp_.resize(tp_size_);
  }

  ~ThreadPool() = default;

  ThreadPool(const ThreadPool& tp) = delete;
  ThreadPool& operator = (const ThreadPool& tp) = delete;

  void Init() {
    auto func = std::bind(ThreadPool::excute, this);
    for (auto idx = 0; idx < tp_size_; ++idx) {
      tp_[idx] = std::thread(func);
    }
    std::cout << "[thread pool]Filling thread pool of " << tp_.size() << " done!" << std::endl;
  }

  void ShutDown() {
    is_shutdown_ = true;
    conditional_lock_.notify_all();
    for (auto& tp : tp_) {
      if (tp.joinable()) {
        tp.join();
      }
    }
    std::cout << "[thread pool]Shut down thread pool." << std::endl;
  }

  template<typename F, typename... Args>
  decltype(auto) submit(F&& f, Args&&... args) {
    auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
    task_queue_.enqueue([task_ptr]() { (*task_ptr)(); });

    conditional_lock_.notify_one();
    return task_ptr->get_future();
  }

 private:
  static void excute(ThreadPool* tp) {
    auto tid  =std::this_thread::get_id();
    std::cout << "[thread pool]tid:" << tid << " enabled." << std::endl;
    std::function<void()> func;
    while (!tp->is_shutdown_) {
      std::unique_lock<std::mutex> lock(tp->conditional_mutex_);
      if (tp->task_queue_.empty()) {
        tp->conditional_lock_.wait(lock);
      } else if (tp->task_queue_.dequeue(func)) {
        func();
      }
    }  // end while
    std::cout << "[thread pool]tid:" << tid << " closed." << std::endl;
  }
  bool is_shutdown_ = false;
  SafeQueue<std::function<void()>> task_queue_;
  const size_t tp_size_;
  std::vector<std::thread> tp_;
  std::mutex conditional_mutex_;
  std::condition_variable conditional_lock_;
};
