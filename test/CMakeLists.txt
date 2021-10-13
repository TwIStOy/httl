set(TEST_MAIN_SRC test-main.cpp)
add_library(test-main STATIC ${TEST_MAIN_SRC})
target_include_directories(test-main PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test>)

function(add_httl_test name)
  set(sources ${name}.cpp)
  add_executable(${name} ${})
  target_link_libraries(test-main httl)
  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_httl_test(avl-tree-test)

