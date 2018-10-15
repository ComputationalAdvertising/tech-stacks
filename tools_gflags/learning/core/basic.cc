#include "basic.h"
#include <iostream>
#include <gflags/gflags.h>

DECLARE_string(conf_path); 

void Basic::print() {
  std::cout << "hello gflags. num: " << num_ << std::endl; 
  std::cout << "[Test] conf_path: " << FLAGS_conf_path << std::endl;
}
