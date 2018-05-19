#include <iostream>

class Test {
public:
  Test() {}
  ~Test() {}

  void print() { 
    std::cout << "hello gflags. num: " << num_ << std::endl; 
  }

private:
  int num_ = 10;
};
