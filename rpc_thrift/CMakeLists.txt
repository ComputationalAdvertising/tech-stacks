cmake_minimum_required(VERSION 2.4)

project(rpc_thrift)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3")

include_directories(
  $ENV{THRIFT_HOME}/include
)

link_directories(
  $ENV{THRIFT_HOME}/lib 
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_libs
  -pthread
  libthrift.a 
  libthrift_c_glib.a
  libthriftnb.a 
  libthriftz.a
)

add_subdirectory(learning)
