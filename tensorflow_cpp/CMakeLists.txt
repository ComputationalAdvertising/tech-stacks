cmake_minimum_required(VERSION 2.4)

project(tensorflow_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=gnu++11")

include_directories(
  $ENV{TENSORFLOW_HOME}
  $ENV{TENSORFLOW_HOME}/bazel-genfiles 
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/downloads/eigen
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/downloads/nsync/public
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/gen/protobuf/include 
)

link_directories(
  $ENV{TENSORFLOW_HOME}/bazel-bin/tensorflow
  $ENV{TENSORFLOW_HOME}/tensorflow/contrib/makefile/gen/protobuf/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_library_names
  -pthread
  tensorflow_cc
  tensorflow_framework
)

add_subdirectory(learning)
