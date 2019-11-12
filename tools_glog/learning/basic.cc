#include <glog/logging.h>
#include <thread>
#include "timer.h"

static int N = 1000;

void test_thread() {
  for (int i = 0; i < N; ++i) {
    sleep(1);
    LOG(INFO) << "I love this world!!! " 
      << std::this_thread::get_id() 
      << " ["<< i << "] in " << N;
  }
  //LOG(ERROR) << std::this_thread::get_id() << "ERROR OPENMIT!"; 
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]); // init glog 
  FLAGS_colorlogtostderr = false;
  FLAGS_logtostderr = false;
  FLAGS_alsologtostderr = false;
  FLAGS_log_dir = "./log";
  //FLAGS_stderrthreshold = google::INFO;
  FLAGS_stderrthreshold = google::FATAL;
  //google::ParseCommandLineFlags(&argc, &argv, true); // init gflags
  
  LOG(INFO) << "TEST";

  openmi::Timer timer;

  std::thread t1(test_thread);
  std::thread t2(test_thread);
  std::thread t3(test_thread);
  std::thread t4(test_thread);
  std::thread t5(test_thread);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  int end_time = timer.Elapsed();
  printf("[%d] per: %f\n", 5*N, 5*N*1.0 / (end_time*1.0/1e6));
  
  google::ShutdownGoogleLogging();
  return 0;
}
