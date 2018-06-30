cmake_minimum_required(VERSION 2.4) 

aux_source_directory(${PROJECT_SOURCE_DIR}/learning/openmit_common openmit_common)

set(sources "")
list(APPEND sources ${sources_openmit_common})

set(curlib openmit_common)
add_library(${curlib} STATIC ${sources})
target_link_libraries(${curlib} ${link_libs})

function (add_program arg)
  list(LENGTH ARGV  argv_len)
  if (NOT (${argv_len} STREQUAL "1")) 
    message(FATAL_ERROR "argment number should be equals to 1")
  endif()

  set(prog_name ${ARGV0})
  message(STATUS "exec_name: ${prog_name}, src_name: ${prog_name}.cc")
  add_executable(${prog_name} "${prog_name}.cc")
  target_link_libraries(${prog_name} ${curlib} ${link_libs})
endfunction()

add_program("synchronizer_test")
