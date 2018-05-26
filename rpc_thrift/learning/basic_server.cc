#include <iostream>
#include <stdexcept>
#include <sstream> 
#include <map>

#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>
#include <thrift/stdcxx.h>

#include "gen-cpp/Predictor.h"

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace shared;
using namespace zy;

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
    return inst.seq_id * 0.01;
  }
};

// Hadnler Factory
class PredictorCloneFactory : virtual public PredictorIfFactory {
public:
  virtual ~PredictorCloneFactory() {}

  virtual PredictorIf* getHandler(const TConnectionInfo& connInfo) {
      stdcxx::shared_ptr<TSocket> sock = stdcxx::dynamic_pointer_cast<TSocket>(connInfo.transport);
    std::cout << "Incoming connection" << "\thost: " << sock->getPeerHost() << ", port: " << sock->getPeerPort() << std::endl;
    return new PredictorHandler;
  }

  virtual void releaseHandler(shared::SharedServiceIf* handler) {
    delete handler;
  }
};

int main(int argc, char** argv) {
  stdcxx::shared_ptr<TServerSocket> socket(new TServerSocket(9090));
  stdcxx::shared_ptr<TBufferedTransportFactory> transport(new TBufferedTransportFactory());
  stdcxx::shared_ptr<TBinaryProtocolFactory> protocol(new TBinaryProtocolFactory());

  stdcxx::shared_ptr<PredictorCloneFactory> calculatorClone(new PredictorCloneFactory());
  stdcxx::shared_ptr<PredictorProcessorFactory> processor(new PredictorProcessorFactory(calculatorClone));

  TThreadedServer server(processor, socket, transport, protocol);

  std::cout << "Starting the server ..." << std::endl;
  server.serve();
  std::cout << "Done." << std::endl;
  return 0;
}
