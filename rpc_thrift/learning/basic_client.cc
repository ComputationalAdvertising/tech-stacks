#include <memory>
#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/stdcxx.h> 

#include "gen-cpp/Predictor.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport; 

using namespace zy;
using namespace shared;

int main(int argc, char** argv) {
  std::string hostname("localhost");
  int port = 9090;
  std::shared_ptr<TSocket> socket(new TSocket(hostname, port));
  std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport)); 
  PredictorClient client(protocol);

  try {
    transport->open();
    std::string ping_info;
    client.ping(ping_info);
    std::cout << "ping result from server: " << ping_info << std::endl;

    Instance inst;
    inst.seq_id = 101;
    inst.line = "line";

    for (auto i = 0; i < 10; ++i) {
      std::cout << "predictor: " << client.predict(inst) << std::endl;
    }
  } catch (TException& tx) {
    std::cout << "Error: " << tx.what() << std::endl;
  }
  return 0;
}
