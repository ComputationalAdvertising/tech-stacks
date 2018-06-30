/*!
 *  Copyright (c) 2017 by Contributors
 *  \file thrift_client_wrapper.h
 *  \brief thrift client wrapper
 */
#ifndef OPENMIT_COMMON_THRIFT_CLIENT_WRAPPER_H_
#define OPENMIT_COMMON_THRIFT_CLIENT_WRAPPER_H_

#include <boost/shared_ptr.hpp>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <thrift/transport/TSocketPool.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include <string>
#include <vector>

using namespace openmit::thrift;
using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

namespace openmit {
namespace common {

template<class Client>
class ThriftClientWrapper {
public:
  ThriftClientWrapper(const std::vector<std::string>& hosts, const std::vector<int>& ports, const int conn_timeout = 0, int timeout = 0): timeout_(timeout) {
    InitThriftClient(hosts, ports, conn_timeout, timeout);
  }

  ThriftClientWrapper(const std::string& host, const int port, const int conn_timeout = 0, int timeout = 0) {
    InitThriftClient(host, port, conn_timeout, timeout);
  }

  ~ThriftClientWrapper() {}

  inline std::shared_ptr<Client> GetThriftClient() { return client_; }

public:
  void InitThriftClient(const std::vector<std::string>& hosts, const std::vector<int>& ports, const int conn_timeout = 0, int timeout = 0);
  void InitThriftClient(const std::string& host, const int port, const int conn_timeout = 0, int timeout = 0);

private:
  std::shared_ptr<Client> client_;
  int timeout_;
};

template<class Client>
void ThriftClientWrapper<Client>::InitThriftClient(const std::vector<std::string>& hosts, const std::vector<int>& ports, const int conn_timeout, int timeout) {
  boost::shared_ptr<TSocket> socket;
  if (hosts.size() > 1 || ports.size() > 1) {
    socket.reset(new TSocketPool(hosts, ports));
  } else {
    socket.reset(new TSocket(hosts[0], ports[0]));
  }

  if (conn_timeout) {
    socket->setConnTimeout(conn_timeout);
  } else if (timeout) {
    socket->setConnTimeout(timeout);
  }

  if (timeout) {
    socket->setSendTimeout(timeout);
    socket->setRecvTimeout(timeout);
  }
  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  client_.reset(new Client(protocol));
}

template<class Client>
void ThriftClientWrapper<Client>::InitThriftClient(const std::string& host, const int port, const int conn_timeout, int timeout) {
  boost::shared_ptr<TSocket> socket(new TSocket(host, port));

  if (conn_timeout) {
    socket->setConnTimeout(conn_timeout);
  } else if (timeout) {
    socket->setConnTimeout(timeout);
  }

  if (timeout) {
    socket->setSendTimeout(timeout);
    socket->setRecvTimeout(timeout);
  }

  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  client_.reset(new Client(protocol));
}

} // namespace common 
} // namespace openmit

#endif // OPENMIT_COMMON_THRIFT_CLIENT_WRAPPER_H_
