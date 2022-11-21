cmake_minimum_required(VERSION 3.12)

include(CheckCXXCompilerFlag)

# Fallback for using newer policies on CMake <3.12.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if(NOT DEFINED HTTL_MASTER_PROJECT)
  set(HTTL_MASTER_PROJECT OFF)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(HTTL_MASTER_PROJECT ON)
    message(STATUS "CMake Version: ${CMAKE_VERSION}")
    message(STATUS "MASTER PROJECT NOW")
  endif()
endif()

option(HTTL_TEST "Generate test targets" ${HTTL_MASTER_PROJECT})
option(HTTL_FMT_EXTERNAL "Use external fmt library instead of bundled" OFF)
option(HTTL_RANGE_EXTERNAL "Use external ranges-v3 library instead of bundled"
       OFF)
option(HTTL_INSTALL "Generate the install target" ${HTTL_MASTER_PROJECT})

project(httl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add custom cmake scripts
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(PEDANTIC_COMPILE_FLAGS
      -pedantic-errors
      -Wall
      -Wextra
      -pedantic
      -Wold-style-cast
      -Wundef
      -Wredundant-decls
      -Wwrite-strings
      -Wpointer-arith
      -Wcast-qual
      -Wformat=2
      -Wmissing-include-dirs
      -Wcast-align
      -Wctor-dtor-privacy
      -Wdisabled-optimization
      -Winvalid-pch
      -Woverloaded-virtual
      -Wconversion
      -Wswitch-enum
      -Wundef
      -Wno-ctor-dtor-privacy
      -Wno-format-nonliteral)
  if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
    set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wno-dangling-else
                               -Wno-unused-local-typedefs)
  endif()
  if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
    set(PEDANTIC_COMPILE_FLAGS
        ${PEDANTIC_COMPILE_FLAGS}
        -Wdouble-promotion
        -Wtrampolines
        -Wzero-as-null-pointer-constant
        -Wuseless-cast
        -Wvector-operation-performance
        -Wsized-deallocation
        -Wshadow)
  endif()
  if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
    set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wshift-overflow=2
                               -Wnull-dereference -Wduplicated-cond)
  endif()
  set(WERROR_FLAG -Werror)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(PEDANTIC_COMPILE_FLAGS
      -Wall
      -Wextra
      -pedantic
      -Wconversion
      -Wundef
      -Wdeprecated
      -Wweak-vtables
      -Wshadow
      -Wno-gnu-zero-variadic-macro-arguments)
  check_cxx_compiler_flag(-Wzero-as-null-pointer-constant HAS_NULLPTR_WARNING)
  if(HAS_NULLPTR_WARNING)
    set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
                               -Wzero-as-null-pointer-constant)
  endif()
  set(WERROR_FLAG -Werror)
endif()

if(MSVC)
  set(PEDANTIC_COMPILE_FLAGS /W3)
  set(WERROR_FLAG /WX)
endif()

# add_library(httl ${HTTL_HEADERS})
add_library(httl INTERFACE)
add_library(httl::httl ALIAS httl)

target_include_directories(
  httl INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if(NOT HTTL_FMT_EXTERNAL)
  add_subdirectory(third_party/fmt)
else()
  if(NOT TARGET fmt::fmt)
    find_package(fmt CONFIG REQUIRED)
  endif()

  set(PKG_CONFIG_REQUIRES fmt)
endif()

if(NOT HTTL_RANGE_EXTERNAL)
  add_subdirectory(third_party/range-v3)
else()
  if(NOT TARGET range-v3)
    find_package(range-v3 CONFIG REQUIRED)
  endif()

  set(PKG_CONFIG_REQUIRES range-v3)
endif()

# target_compile_definitions(httl INTERFACE HTTL_FMT_EXTERNAL)
target_link_libraries(httl INTERFACE fmt::fmt)
target_link_libraries(httl INTERFACE range-v3)

if(HTTL_TEST AND HTTL_MASTER_PROJECT)
  enable_testing()
  add_subdirectory(third_party/Catch2)
  add_subdirectory(test)
endif()

if(HTTL_INSTALL)
  message(STATUS "Generating install")
  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(
    TARGETS httl
    EXPORT httl
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
