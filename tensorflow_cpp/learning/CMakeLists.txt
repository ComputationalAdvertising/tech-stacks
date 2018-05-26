#aux_source_directory(core SOURCES_CORE)
#
#set(SOURCES 
#  ${SOURCES_CORE}
#)
#
#set(static_lib tstensorflowcpp)
#add_library(${static_lib} STATIC ${SOURCES})
#target_link_libraries(${static_lib} ${link_library_names}) 

#set(exec "tf_session")
#add_executable(${exec} "${exec}.cc")
#target_link_libraries(${exec} ${link_library_names})

#set(exec "client_session_test")
set(exec "string_ops_test")
add_executable(${exec} "${exec}.cc" ${SOURCES_CC_FRAMEWORK})
target_link_libraries(${exec} ${link_library_names})

aux_source_directory($ENV{TENSORFLOW_HOME}/tensorflow/cc/framework SOURCES_CC_FRAMEWORK)
set(exec "cc_op_gen_test")
add_executable(${exec} "${exec}.cc" ${SOURCES_CC_FRAMEWORK})
target_link_libraries(${exec} ${link_library_names})
