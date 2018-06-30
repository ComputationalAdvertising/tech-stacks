#include "ps_handler.h"
#include "thrift_server_wrapper.h"

#include <boost/shared_ptr.hpp>
#include <glog/logging.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TNonblockingServer.h>

#include <string>

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::server;
using namespace apache::thrift::transport;

using namespace openmit::common;
using namespace openmit::ps;

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
  int num_thread = 2;
  int num_io_thread = 1;
  int port = 4321;
  std::string mode = "offline"; 

  boost::shared_ptr<PsIf> handler(new PsHandler(mode));
  boost::shared_ptr<TProcessor> processor(new PsProcessor(handler));

  std::shared_ptr<ThriftServerWrapper> thrift_server_wrapper;
  thrift_server_wrapper = std::make_shared<ThriftServerWrapper>(processor, port, num_thread, num_io_thread);
  boost::shared_ptr<ThreadManager> thread_mgr = thrift_server_wrapper->GetThreadManager();
  std::shared_ptr<TNonblockingServer> server = thrift_server_wrapper->GetThriftServer();
  
  LOG(WARNING) << "Init NonBlockingServer for mode: " << mode << ", port: " << port << ", num_thread: " << num_thread << ", num_io_thread: " << num_io_thread;
  server->serve();
  
  LOG(INFO) << "PS done.";
  return 0;
}
