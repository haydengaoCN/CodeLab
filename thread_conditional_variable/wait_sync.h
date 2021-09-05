#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <unordered_map>

class ParallelWriter {
 public:
  ParallelWriter(int num_areas_to_be_writen) :
      task_counts_(num_areas_to_be_writen), kTotalThreads(num_areas_to_be_writen) {
    init(num_areas_to_be_writen);
  }
  ~ParallelWriter();

  // return false when failed to excute tasks
  bool wait_to_sync();
  void create_work(const std::string& work);
 
 private:
  void init(int num_areas_to_be_writen);
  void wait_to_get_work(int area);
  void do_work(int area);
  void do_real_work(int area);
  void count_down_and_try_to_notify();

  int task_counts_{0};
  bool tasks_all_set_{false};
  const int kTotalThreads;
  std::unordered_map<int, std::string> tasks_;
  std::unordered_map<int, bool> results_;
  std::unordered_map<int, std::thread> threads_;
  std::mutex mutex_to_access_data_;
  std::mutex mutex_to_sync_tasks_;
  std::condition_variable con_var_to_access_data_;
  std::condition_variable con_var_to_sync_tasks_;
};