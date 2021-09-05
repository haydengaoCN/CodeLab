// date: 20210204
// author: haydengao
// describe: for the time of touching fish

#pragma once

#include <mutex>
#include <queue>

template<typename T>
class SafeQueue {
 public:
  SafeQueue() = default;
  ~SafeQueue() = default;
  bool empty() {
    std::unique_lock<std::mutex> scope_lock(m_mutex_);
    return m_queue_.empty();
  }
  int size() {
    std::unique_lock<std::mutex> scope_lock(m_mutex_);
    return m_queue_.size();
  }
  void enqueue(T&& t) {
    std::unique_lock<std::mutex> scope_lock(m_mutex_);
    m_queue_.emplace(t);
  }
  bool dequeue(T& t) {
    std::unique_lock<std::mutex> scope_lock(m_mutex_);
    if (m_queue_.empty()) {
      return false;
    }
    t = std::move(m_queue_.front());
    m_queue_.pop();
    return true;
  }
 private:
  std::queue<T> m_queue_;
  std::mutex m_mutex_;
};
