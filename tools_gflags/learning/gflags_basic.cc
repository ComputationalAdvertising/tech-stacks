#include <gflags/gflags.h>
#include <cstdio>
#include <functional>
#include <iostream>
#include "core/basic.h"

DEFINE_string(conf_path, "", "program configure file.");
DEFINE_int32(port, 9090, "program listen port.");
DEFINE_bool(daemon, true, "run daemon mode.");


int callback(int i, int j, const std::string& str) {
  printf("%i + %i = %i, str: %s\n\n", i, j, i+j, str.c_str());
  return i + j;
}


int main(int argc, char** argv) {
  std::cout << "argc: " << argc << "\n print argv:\n" << std::endl;
  for (int i = 0; i < argc; ++i) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  printf("-------------- here ---------------\n");
  gflags::SetVersionString("1.0.0.0");
  gflags::SetUsageMessage("Usage: ./demo");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::cout << "conf_path = " << FLAGS_conf_path << std::endl;
  std::cout << "port = " << FLAGS_port << std::endl;
  if (FLAGS_daemon) {
    std::cout << "daemon = true. run true task." << std::endl;
  } else {
    std::cout << "daemon = false. run false task." << std::endl;
  }
  std::cout << "done. gflags::ShutDown" << std::endl;
  gflags::ShutDownCommandLineFlags(); 

  std::string str("callback");
  std::function<int(int i, int j)> create_kernel;
  auto lambda = [str](int i, int j) -> int {
    return callback(i, j, str);
  };
  create_kernel = lambda;

  std::cout << "i+j: " << create_kernel(10, 20) << std::endl; 

  Test test;
  test.print();

  return 0;
}
