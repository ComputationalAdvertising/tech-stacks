#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <sstream> 

#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h> 

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TNonblockingServer.h>

#include "gen-cpp/Predictor.h"
#include "instance.pb.h"

#include "ps_handler.h"

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace shared;
using namespace zy;
using namespace openmit::ps;

// Complete a handler
class PredictorHandler : public PredictorIf {
public:
  PredictorHandler() {}
    
  void ping(std::string& _return) { _return = "tell client ping success."; std::cout << "ping " << std::endl; }

  void get_instance(Instance& res, const Instance& inst) {
    res.seq_id = inst.seq_id + 1;
    res.line = inst.line;
  }
  
  void getStruct(SharedStruct& ret, const int32_t logid) {
      std::cout << "getStruct(" << logid << ")" << std::endl;
  }

  double predict(const Instance& inst) {
    std::cout << "[predict] inst.seq_id: " << inst.seq_id << std::endl;
    return inst.seq_id * 0.01;
  } 

  void TestBinary(const std::string& bin) {
    openmit::pb::Features features;
    features.ParseFromArray(bin.c_str(), bin.size());
    std::cout << "TestBinary features.DebugString: " << features.DebugString() << std::endl;
    std::cout << "[TMP] TestBinary:\n" << bin << std::endl;
  }
};

// Hadnler Factory
class PredictorCloneFactory : virtual public PredictorIfFactory {
public:
  virtual ~PredictorCloneFactory() {}

  virtual PredictorIf* getHandler(const TConnectionInfo& connInfo) {
      //boost::shared_ptr<TSocket> sock = std::dynamic_pointer_cast<TSocket>(connInfo.transport);
    boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
    std::cout << "Incoming connection" << "\thost: " << sock->getPeerHost() << ", port: " << sock->getPeerPort() << std::endl;
    return new PredictorHandler;
  }

  virtual void releaseHandler(shared::SharedServiceIf* handler) {
    delete handler;
  }
};

int main(int argc, char** argv) {
  //boost::shared_ptr<TServerSocket> socket(new TServerSocket(9090));
  //boost::shared_ptr<TBufferedTransportFactory> transport(new TBufferedTransportFactory());
  
  //boost::shared_ptr<TBinaryProtocolFactory> protocol(new TBinaryProtocolFactory());
  //boost::shared_ptr<PredictorCloneFactory> calculatorClone(new PredictorCloneFactory());
  //boost::shared_ptr<PredictorProcessorFactory> processor(new PredictorProcessorFactory(calculatorClone)); 
  //TThreadedServer server(processor, socket, transport, protocol);

  //boost::shared_ptr<PredictorIf> handler(new PredictorHandler());
  //boost::shared_ptr<TProcessor> processor(new PredictorProcessor(handler));
  std::string mode("offline");
  boost::shared_ptr<PsIf> handler(new PsHandler(mode));
  boost::shared_ptr<TProcessor> processor(new PsProcessor(handler));
  boost::shared_ptr<TProtocolFactory> protocol_factory(new TBinaryProtocolFactory());
  boost::shared_ptr<ThreadManager> thread_mgr(ThreadManager::newSimpleThreadManager(2));
  boost::shared_ptr<PosixThreadFactory> thread_factory(new PosixThreadFactory());
  thread_mgr->threadFactory(thread_factory);
  thread_mgr->start();

  std::cout << "Starting the server ..." << std::endl;
  TNonblockingServer server(processor, protocol_factory, 9090, thread_mgr);
  server.setNumIOThreads(1);
  std::string ps_mode = "offline";
  server.serve();
  std::cout << "Done." << std::endl;
  return 0;
}
