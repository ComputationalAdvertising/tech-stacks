cmake_minimum_required(VERSION 2.4) 

aux_source_directory(gen-cpp sources_gencpp)
list(REMOVE_ITEM sources_gencpp "gen-cpp/Calculator_server.skeleton.cpp")
list(REMOVE_ITEM sources_gencpp "gen-cpp/SharedService_server.skeleton.cpp")

set(curlib tfrpcthrift)
add_library(${curlib} STATIC ${sources_gencpp})
target_link_libraries(${curlib} ${link_libs})

function (add_program arg)
  list(LENGTH ARGV  argv_len)
  if (NOT (${argv_len} STREQUAL "2")) 
    message(FATAL_ERROR "argment number should be equals to 2")
  endif()

  set(exec_name ${ARGV0})
  set(src_name ${ARGV1})
  message(STATUS "exec_name: ${exec_name}, src_name: ${src_name}")
  add_executable(${exec_name} "${src_name}")
  target_link_libraries(${exec_name} ${curlib} ${link_libs})

endfunction()

add_program("app_client" "app_client.cc")
add_program("app_server" "app_server.cc")
