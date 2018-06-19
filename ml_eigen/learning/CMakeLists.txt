cmake_minimum_required(VERSION 2.4) 


function (add_program arg)
  list(LENGTH ARGV  argv_len)
  if (NOT (${argv_len} STREQUAL "1")) 
    message(FATAL_ERROR "argment number should be equals to 1")
  endif()

  set(prog_name ${ARGV0})
  message(STATUS "exec_name: ${prog_name}, src_name: ${prog_name}.cc")
  add_executable(${prog_name} "${prog_name}.cc")
  target_link_libraries(${prog_name})
endfunction()

add_program("basic_matrix")
