#include "timer.h"

#include <glog/logging.h>

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace openmit;

typedef std::shared_ptr<std::thread> ThreadPtr;

std::vector<std::string> insts;

void Parse(int thread_idx, int total_thread_num, std::vector<std::string>& insts) {
  common::Timer timer;
  for (auto i = thread_idx; i < insts.size(); i += total_thread_num) {
    LOG(INFO) << "[thread-" << thread_idx << "] " << insts[i];
  }
  int total_time = timer.Elapsed();
  LOG(INFO) << "[thread-" << thread_idx << " total_time] " << total_time;
}

void MultiThreadDataParse(int num_thread) {
  //std::vector<ThreadPtr> thread_pools;
  std::vector<std::shared_ptr<std::thread> > thread_pools;
  for (int i = 0; i < num_thread; ++i) {
    auto thread = std::make_shared<std::thread> (Parse, i, num_thread, std::ref(insts));
    thread_pools.emplace_back(thread);
  }
  LOG(INFO) << "Wait for Parse ...";
  for (auto& tp: thread_pools) {
    tp->join();
  }
  LOG(INFO) << "task complete.";
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;

  int total_inst_num = 0;
  int valid_inst_num = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    total_inst_num += 1;
    if (!line.size()) continue;
    valid_inst_num += 1;
    insts.emplace_back(line);
  }
  LOG(INFO) << "read finished. total_inst_num: " << total_inst_num << ", valid_inst_num: " << valid_inst_num << ", insts.size: " << insts.size();

  MultiThreadDataParse(4);

  return 0;
}
