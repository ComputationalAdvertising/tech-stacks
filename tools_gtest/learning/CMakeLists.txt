#aux_source_directory(core SOURCES_CORE)
#
#set(SOURCES 
#  ${SOURCES_CORE}
#)
#
#set(static_lib tstoolsgflags)
#add_library(${static_lib} STATIC ${SOURCES})
#target_link_libraries(${static_lib} ${link_library_names}) 

set(exec "sample1_unittest")
add_executable(${exec} "${exec}.cc" "sample1.h" "sample1.cc")
target_link_libraries(${exec} ${link_library_names})

set(exec "sample10_unittest")
add_executable(${exec} "${exec}.cc")
target_link_libraries(${exec} ${link_library_names})
