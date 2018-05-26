#include <iostream>
#include <memory>
#include <string>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/stdcxx.h> 

#include <snappy.h>

#include "gen-cpp/Predictor.h"
#include "instance.pb.h"

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

    openmit::pb::Features features;
    for (int j = 0; j < 1000; j++) {
      openmit::pb::DenseFeature* dense = features.add_dense();
      for (int k = 0; k < 100; ++k) {
        dense->add_values(k*0.1f);
      }
      for (int i = 0; i < 1000; ++i) {
        dense->add_values(0.01f * j + i);
      }
      dense->set_type("ctr");
    }
    std::string pb_str;
    features.SerializeToString(&pb_str);
    std::cout << "features_len: " << pb_str.size() << ", ByteSizeLong: " << features.ByteSizeLong() << std::endl;

    Instance inst;
    inst.seq_id = 101;
    inst.line = "line";

    snappy::Compress(pb_str.c_str(), pb_str.size(), &(inst.data)); 
    
    size_t uncompress_len = 0;
    if (snappy::GetUncompressedLength(inst.data.c_str(), inst.data.size(), &uncompress_len) == false) {
      std::cerr << "get uncompress len failed.\n";
      return -1;
    }

    std::string uncompress_buffer;
    if (snappy::Uncompress(inst.data.c_str(), inst.data.size(), &uncompress_buffer) == false) {
      std::cerr << "uncompress data failed.";
      return -1;
              
    }
    std::cout << "compress_len: " << inst.data.size() << ", uncompress_len: " << uncompress_len << ", buffer.size: " << uncompress_buffer.size() << std::endl;

    openmit::pb::Features features_fill;
    features_fill.ParseFromArray(uncompress_buffer.c_str(), uncompress_buffer.size());
    //std::cout << features_fill.dense(1).DebugString() << std::endl;

    for (auto i = 0; i < 10; ++i) {
      std::cout << "predictor: " << client.predict(inst) << std::endl;
    }
  } catch (TException& tx) {
    std::cout << "Error: " << tx.what() << std::endl;
  }
  return 0;
}
