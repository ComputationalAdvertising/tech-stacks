aux_source_directory(core SOURCES_CORE)

set(SOURCES 
  ${SOURCES_CORE}
)

set(static_lib tstoolsgflags)
add_library(${static_lib} STATIC ${SOURCES})
target_link_libraries(${static_lib} ${link_library_names}) 

#set(exec "gflags_basic")
set(exec "basic_test")
add_executable(${exec} "${exec}.cc" ${SOURCES})
target_link_libraries(${exec} ${link_library_names})
