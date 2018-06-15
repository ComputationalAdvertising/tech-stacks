set(exec "greeter_client")
add_executable(${exec} "${exec}.cc")
target_link_libraries(${exec} ${link_libs} mitgrpcproto)
set(exec "greeter_server")
add_executable(${exec} "${exec}.cc")
target_link_libraries(${exec} ${link_libs} mitgrpcproto)

