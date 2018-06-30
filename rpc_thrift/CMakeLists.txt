cmake_minimum_required(VERSION 2.4)

project(rpc_thrift)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_NETINET_IN_H")

include_directories(
  $ENV{THRIFT_HOME}/include 
  $ENV{PROTOBUF_HOME}/include 
  ${PROJECT_SOURCE_DIR}/gen-pb/cpp 
  ${PROJECT_SOURCE_DIR}/third_party/deps/libevent/include
  ${PROJECT_SOURCE_DIR}/third_party/deps/snappy/include
  ${PROJECT_SOURCE_DIR}/../tools_glog/third_party/deps/glog/include
  ${PROJECT_SOURCE_DIR}/../tools_gflags/third_party/deps/include
  ${PROJECT_SOURCE_DIR}/learning/openmit-common
  ${PROJECT_SOURCE_DIR}/learning/openmit-ps
  ${PROJECT_SOURCE_DIR}/learning/openmit-idl/gen-cpp
)

link_directories(
  $ENV{THRIFT_HOME}/lib 
  $ENV{PROTOBUF_HOME}/lib
  ${PROJECT_SOURCE_DIR}/third_party/deps/libevent/lib
  ${PROJECT_SOURCE_DIR}/third_party/deps/snappy/lib
  ${PROJECT_SOURCE_DIR}/../tools_glog/third_party/deps/glog/lib
  ${PROJECT_SOURCE_DIR}/../tools_gflags/third_party/deps/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

  #libthrift_c_glib.a
  #libthriftc.a 
  #libthriftz.a
set(link_libs
  -pthread 
  libthriftnb.a 
  libthrift.a 
  libprotobuf.a
  libprotoc.a
  libprotobuf-lite.a
  libsnappy.a
  libevent.a
  libevent_core.a
  libevent_extra.a
  libevent_openssl.a
  libevent_pthreads.a 
  libglog.a
  libgflags.a
)

#add_subdirectory(learning)
add_subdirectory(learning/openmit-common)
