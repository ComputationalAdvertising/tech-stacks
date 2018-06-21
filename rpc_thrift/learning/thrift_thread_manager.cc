#include <iostream>
#include <set>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/Monitor.h>
#include <thrift/server/TSimpleServer.h>
#include <boost/shared_ptr.hpp>

using namespace apache::thrift::concurrency;
using namespace apache::thrift::server;

class MyTask : public Runnable {
public:
  MyTask(Monitor& monitor, int& count): monitor_(monitor), count_(count) {
    std::cout << "MyTask constructor!!!" << std::endl;
  }

  void run() {
    Synchronized s(monitor_);
    count_++;
    if (count_ == 10) {
      std::cout << "count_ == 10. notify ..." << std::endl;
      monitor_.notify();
    }
  }

private:
  int& count_;
  Monitor& monitor_;
};

int main(int argc, char** argv) {
  int num_threads = 5;
  boost::shared_ptr<ThreadManager> thread_manager = ThreadManager::newSimpleThreadManager(num_threads);
  boost::shared_ptr<PosixThreadFactory> thread_factory(new PosixThreadFactory());
  thread_manager->threadFactory(thread_factory);
  thread_manager->start(); 

  Monitor monitor;
  int m = 0;

  std::set<boost::shared_ptr<MyTask> > tasks;
  for (int i = 0; i < 20; ++i) {
    tasks.insert(boost::shared_ptr<MyTask>(new MyTask(monitor, m)));
  }

  std::set<boost::shared_ptr<MyTask> >::iterator it;
  for (it = tasks.begin(); it != tasks.end(); ++it) {
    thread_manager->add(*it, 50, 50);
  }

  { 
    // Synchroized 使用了RAII 方式
    Synchronized s(monitor);
    monitor.wait();
  }
  //thread_manager->join();  // ThreadManager’ has no member named ‘join’
  thread_manager->stop();
  return 0;
}
