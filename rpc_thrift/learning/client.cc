#include "Ps.h"
#include "thrift_client_wrapper.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <gflags/gflags.h>
#include <glog/logging.h>

#include <string>
#include <vector>

using namespace openmit::common;
using namespace openmit::thrift;

DEFINE_string(hosts, "localhost", "ps cluster hostname list");
DEFINE_string(ports, "4321", "ps port list");
DEFINE_int32(conn_timeout, 100, "connection timeout");
DEFINE_int32(timeout, 500, "send/recv timeout");

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]); // exec file
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_stderrthreshold = google::INFO;
  
  LOG(INFO) << "FLAGS_hosts: " << FLAGS_hosts;
  LOG(INFO) << "FLAGS_ports: " << FLAGS_ports;
  std::vector<std::string> hosts;
  boost::split(hosts, FLAGS_hosts, boost::is_any_of(","));
  std::vector<std::string> ports_str;
  boost::split(ports_str, FLAGS_ports, boost::is_any_of(",")); 
  std::vector<int> ports;
  for (auto& port: ports_str) { 
    ports.emplace_back(boost::lexical_cast<int>(port));
  }
  
  std::shared_ptr<ThriftClientWrapper<PsClient> > thrift_client_wrapper;
  thrift_client_wrapper.reset(new ThriftClientWrapper<PsClient>(hosts, ports, FLAGS_conn_timeout, FLAGS_timeout));
  std::shared_ptr<PsClient> client = thrift_client_wrapper->GetThriftClient();
  
  try {
    client->getInputProtocol()->getTransport()->open();
    LOG(INFO) << "NumServer: " << client->NumServer();
    std::string mode;
    client->Mode(mode);
    LOG(INFO) << "Mode: " << mode;
    LOG(INFO) << "use_count: " << client.use_count();
  } catch (TException& tx) {
    LOG(ERROR) << "TException " << tx.what();
  }

  gflags::ShutDownCommandLineFlags();
}
