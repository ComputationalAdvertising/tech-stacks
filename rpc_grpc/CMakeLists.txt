cmake_minimum_required(VERSION 2.4)

project(rpc_grpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -fPIC -mssse3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_NETINET_IN_H")

include_directories(
  ${PROJECT_SOURCE_DIR}/gen-pb/cpp 
  $ENV{GRPC_HOME}/include
  $ENV{PROTOBUF_HOME}/include
)
  #${PROJECT_SOURCE_DIR}/third_party/deps/grpc/include

  #${PROJECT_SOURCE_DIR}/third_party/deps/grpc/lib
link_directories(
  $ENV{GRPC_HOME}/lib
  $ENV{PROTOBUF_HOME}/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

set(link_libs
  -pthread
  libgrpc.a
  libgrpc++.a
  libgrpc++_cronet.a
  libgrpc++_error_details.a
  libgrpc++_reflection.a
  libprotobuf.a
  libprotoc.a
  libprotobuf-lite.a
)
  #libgrpc++.a

# static lib 
aux_source_directory(gen-pb/cpp SRCS_PROTO)
set(SOURCES ${SRCS_PROTO})
set(static_lib_name mitgrpcproto)
add_library(${static_lib_name} STATIC ${SOURCES})
set_target_properties(${static_lib_name} PROPERTIES OUTPUT "mitgrpcproto")
set_target_properties(${static_lib_name} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(${static_lib_name} ${link_libs})

add_subdirectory(learning)
