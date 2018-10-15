cmake_minimum_required(VERSION 2.4)

project(tools_gflags)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=c++11")

include_directories(
  ${PROJECT_SOURCE_DIR}/third_party/deps/include 
  ${PROJECT_SOURCE_DIR}/learning
)

link_directories(
  ${PROJECT_SOURCE_DIR}/third_party/deps/lib 
  ${PROJECT_SOURCE_DIR}
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_library_names
  -pthread
  gflags
  gflags_nothreads
)

add_subdirectory(learning)
