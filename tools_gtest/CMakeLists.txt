cmake_minimum_required(VERSION 2.4)

project(tools_gflags)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3")

include_directories(
  ${PROJECT_SOURCE_DIR}/third_party/deps/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/third_party/deps/lib 
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_library_names
  -pthread
  gmock
  gtest
  gtest_main
)

add_subdirectory(learning)
