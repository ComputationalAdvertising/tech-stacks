/*!
 *  Copyright (c) 2017 by Contributors
 *  \file ynchronizer.h
 *  \brief task/thread synchronizer
 */
#ifndef OPENMIT_COMMON_SYNCHRONIZER_H_
#define OPENMIT_COMMON_SYNCHRONIZER_H_

#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable 

namespace openmit {
namespace common {

// Task/Thread Synchronizer
class Synchronizer {
public:
  Synchronizer(const std::string& task_name = "SyncTask"): task_name_(task_name) {}
  
  ~Synchronizer() {}
  
  void Wait(int total_num);
  
  void AddFinish(bool task_result); 
  
  inline void Clear();

private:
  int finish_num_ = 0;
  int fail_num_ = 0;
  std::string task_name_;
  std::condition_variable cond_;
  std::mutex mutex_;
};

void Synchronizer::Wait(int total_num) {
  std::unique_lock<std::mutex> lock(mutex_);
  while (total_num != finish_num_) cond_.wait(lock);
  if (fail_num_) {
    throw std::runtime_error("[synchronizer.h] " + task_name_ + ": " 
                             + std::to_string(fail_num_) + " task(s) failed in all " 
                             + std::to_string(total_num) + " tasks!");
  }
}

void Synchronizer::AddFinish(bool task_result) {
  std::lock_guard<std::mutex> lock(mutex_); 
  {
    finish_num_++;
    if (!task_result) fail_num_++;
  }
  cond_.notify_one();
}

void Synchronizer::Clear() {
  finish_num_ = 0;
  fail_num_ = 0;
}

} // namespace common 
} // namespace openmit 

#endif // OPENMIT_COMMON_SYNCHRONIZER_H_
