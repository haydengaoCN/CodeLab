#include "wait_sync.h"

#include <iostream>

void ParallelWriter::init(int num_areas_to_be_writen) {
  for (auto idx = 0; idx < num_areas_to_be_writen; ++idx) {
    std::thread tmp = std::thread([this, idx]() {do_work(idx);});
    // threads_.emplace(tmp, std::move(tmp));
    threads_[idx] = std::move(tmp);
  }
}

ParallelWriter::~ParallelWriter() {
  for (auto& [area, th] : threads_) {
    if (th.joinable()) {
      th.join();
    }
  }
}
void ParallelWriter::do_work (int area) {
  std::cout << "let's do work in area:" << area << std::endl;
  while (true) {
    // block to get tasks
    wait_to_get_work(area);

    do_real_work(area);

    count_down_and_try_to_notify();
  }
}

void ParallelWriter::do_real_work(int area) {
  std::cout << "area:" << area << " is doing the work..." << std::endl;
  results_[area] = true;
}

void ParallelWriter::count_down_and_try_to_notify() {
  std::scoped_lock _scplock(mutex_to_sync_tasks_);
  --task_counts_;
  std::cout << "task_counts:" << task_counts_ << std::endl;
  if (task_counts_ == 0) {
    con_var_to_sync_tasks_.notify_one();
  }
}

bool ParallelWriter::wait_to_sync() {
  {
    std::unique_lock _lck(mutex_to_sync_tasks_);
    con_var_to_sync_tasks_.wait(_lck, [this](){return task_counts_ == 0;});
  }
  // no need lock here
  task_counts_ = kTotalThreads;
  tasks_all_set_ = false;
  bool ret = true;
  for (auto& [_, result] : results_) {
    if (result == false) {
      ret = false;
    }
    result = false;
  }
  return ret;
}

void ParallelWriter::create_work(const std::string& work) {
  std::scoped_lock _scplock(mutex_to_access_data_);
  for (auto idx = 0; idx < kTotalThreads; ++idx) {
    tasks_[idx] = work + "_" + std::to_string(idx);
  }
  tasks_all_set_ = true;
  con_var_to_access_data_.notify_all();
}

void ParallelWriter::wait_to_get_work(int area) {
  std::unique_lock<std::mutex> _lck(mutex_to_access_data_);
  con_var_to_access_data_.wait(_lck, [this](){ return tasks_all_set_;});

  std::cout << "area:" << area << " get work:" << tasks_[area] << std::endl;
}