cmake_minimum_required(VERSION 2.4)

project(rpc_thrift)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_NETINET_IN_H")

include_directories(
  ${PROJECT_SOURCE_DIR}/third_party/deps/eigen/include/eigen3
)

link_directories(
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_libs
)

add_subdirectory(learning)
