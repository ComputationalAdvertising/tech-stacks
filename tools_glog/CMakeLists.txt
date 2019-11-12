cmake_minimum_required(VERSION 2.4)

project(rpc_thrift)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=c++11 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_NETINET_IN_H")

include_directories(
  ${PROJECT_SOURCE_DIR}/third_party/deps/glog/include 
  ${PROJECT_SOURCE_DIR}/../tools_gflags/third_party/deps/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/third_party/deps/glog/lib 
  ${PROJECT_SOURCE_DIR}/../tools_gflags/third_party/deps/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

  #libgflags.a
set(link_libs
  -pthread
  libglog.a 
)

add_subdirectory(learning)
