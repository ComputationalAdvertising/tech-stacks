cmake_minimum_required(VERSION 2.4)

project(openmit-idl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_NETINET_IN_H")

include_directories(
  $ENV{THRIFT_HOME}/include 
  $ENV{PROTOBUF_HOME}/include 
)

link_directories(
  $ENV{THRIFT_HOME}/lib 
  $ENV{PROTOBUF_HOME}/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_libs
  libthrift.a 
  libprotobuf.a
  libprotoc.a
)

aux_source_directory(gen-pb/cpp srcs_pbcpp)
aux_source_directory(gen-thrift/gen-cpp srcs_thriftcpp)
list(REMOVE_ITEM srcs_thriftcpp "gen-thrift/gen-cpp/Ps_server.skeleton.cpp")

set(srcs "")
list(APPEND srcs ${srcs_pbcpp})
list(APPEND srcs ${srcs_thriftcpp}) 

set(libname openmit_idl)
add_library(${libname} STATIC ${srcs})
target_link_libraries(${libname} ${link_libs})
