#include <glog/logging.h>


int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]); // init glog 
  FLAGS_colorlogtostderr = true;
  FLAGS_stderrthreshold = google::INFO;
  //google::ParseCommandLineFlags(&argc, &argv, true); // init gflags
  LOG(INFO) << "Hello OPENMIT!";
  LOG(ERROR) << "ERROR OPENMIT!"; 
  google::ShutdownGoogleLogging();
  return 0;
}
