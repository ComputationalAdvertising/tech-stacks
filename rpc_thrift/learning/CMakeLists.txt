cmake_minimum_required(VERSION 2.4) 

#list(REMOVE_ITEM sources_gencpp "gen-cpp/Calculator_server.skeleton.cpp")
#list(REMOVE_ITEM sources_gencpp "gen-cpp/SharedService_server.skeleton.cpp")
#list(REMOVE_ITEM sources_gencpp "gen-cpp/Predictor_server.skeleton.cpp")
aux_source_directory(openmit-idl/gen-cpp sources_gencpp)
list(REMOVE_ITEM sources_gencpp "openmit-idl/gen-cpp/Ps_server.skeleton.cpp")
aux_source_directory(openmit-common sources_openmit_common)
aux_source_directory(openmit-ps sources_openmit_ps)
aux_source_directory(${PROJECT_SOURCE_DIR}/gen-pb/cpp sources_genpb)

set(sources "")
list(APPEND sources ${sources_gencpp})
list(APPEND sources ${sources_genpb})
list(APPEND sources ${sources_openmit_common})
list(APPEND sources ${sources_openmit_ps})

set(curlib openmitthrift)
add_library(${curlib} STATIC ${sources})
target_link_libraries(${curlib} ${link_libs})

function (add_program arg)
  list(LENGTH ARGV  argv_len)
  if (NOT (${argv_len} STREQUAL "1")) 
    message(FATAL_ERROR "argment number should be equals to 1")
  endif()

  set(prog_name ${ARGV0})
  message(STATUS "exec_name: ${prog_name}, src_name: ${prog_name}.cc")
  #add_executable(${prog_name} "${prog_name}.cc" "ps_handler.cc" "ps_handler.h")
  add_executable(${prog_name} "${prog_name}.cc")
  target_link_libraries(${prog_name} ${curlib} ${link_libs})
endfunction()

#add_program("basic_client")
#add_program("basic_server")

#add_program("basic_pb_client")
#add_program("basic_pb_server") 

#add_program("thrift_thread_manager")

#add_program("client")
#add_program("server")

add_program("synchronizer")
