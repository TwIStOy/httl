function(add_httl_test name)
  set(sources ${name}.cpp)
  add_executable(${name} ${sources})
  target_link_libraries(${name} httl Catch2::Catch2WithMain)
  target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/test)
  target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/include)
  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_httl_test(avl-tree-test)
add_httl_test(stealer-test)

