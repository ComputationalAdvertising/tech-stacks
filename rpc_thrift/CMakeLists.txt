cmake_minimum_required(VERSION 2.4)

project(rpc_thrift)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_NETINET_IN_H")

include_directories(
  $ENV{THRIFT_HOME}/include 
  $ENV{PROTOBUF_HOME}/include 
  ${PROJECT_SOURCE_DIR}/gen-pb/cpp 
  ${PROJECT_SOURCE_DIR}/third_party/deps/snappy/include
)

link_directories(
  $ENV{THRIFT_HOME}/lib 
  $ENV{PROTOBUF_HOME}/lib
  ${PROJECT_SOURCE_DIR}/third_party/deps/snappy/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

  #libthrift_c_glib.a
  #libthriftnb.a 
set(link_libs
  -pthread
  libthrift.a 
  libthriftz.a
  libprotobuf.a
  libprotoc.a
  libprotobuf-lite.a
  libsnappy.a
)

add_subdirectory(learning)
