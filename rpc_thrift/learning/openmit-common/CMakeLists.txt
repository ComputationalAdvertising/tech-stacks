cmake_minimum_required(VERSION 2.4) 

project(openmit-idl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_NETINET_IN_H")

include_directories(
  $ENV{THRIFT_HOME}/include 
  ${PROJECT_SOURCE_DIR}/common
)

link_directories(
  $ENV{THRIFT_HOME}/lib
  ${PROJECT_SOURCE_DIR}
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_libs
  -pthread 
  libthriftnb.a 
  libthrift.a 
  libsnappy.a
  libevent.a
  libevent_core.a
  libevent_extra.a
  libevent_openssl.a
  libevent_pthreads.a
  libglog.a
  libgflags.a
)

aux_source_directory(common srcs_common)
set(srcs "")
list(APPEND srcs ${srcs_common})

set(libname openmit_common)
add_library(${libname} STATIC ${srcs})
target_link_libraries(${libname} ${link_libs}) 

add_subdirectory(test)
