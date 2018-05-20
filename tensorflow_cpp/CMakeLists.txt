cmake_minimum_required(VERSION 2.4)

project(tensorflow_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=gnu++11")

include_directories(
  $ENV{TENSORFLOW_HOME}
  $ENV{TENSORFLOW_HOME}/bazel-genfiles 
  $ENV{TENSORFLOW_HOME}/tensorflow
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/downloads/eigen
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/downloads/nsync/public
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/gen/protobuf/include 
  $ENV{TESNORFLOW_HOME}/tensorflow/contrib/makefile/gen/proto
  ${PROJECT_SOURCE_DIR}/../tools_gtest/third_party/deps/include
)

link_directories(
  $ENV{TENSORFLOW_HOME}/bazel-bin/tensorflow
  $ENV{TENSORFLOW_HOME}/bazel-bin/tensorflow/cc
  $ENV{TENSORFLOW_HOME}/bazel-bin/tensorflow/core
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/gen/protobuf/lib 
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/gen/lib
  ${PROJECT_SOURCE_DIR}/../tools_gtest/third_party/deps/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_library_names
  -pthread
  tensorflow_cc
  tensorflow_framework
  array_grad
  cc_ops_internal
  cc_ops 
  client_session
  const_op 
  data_flow_grad 
  gradients 
  grad_op_registry
  math_grad
  nn_grad
  ops
  scope
  testutil
  while_loop
  abi
  core_cpu_base
  core_cpu_internal
  graph
  lib_proto_parsing
  op_gen_lib
  shape_inference_testutil
  stacktrace_handler
  sycl_runtime
  tensor_testutil
  testlib
  test_main
  test
  gmock
  gtest
  gtest_main
)

add_subdirectory(learning)
