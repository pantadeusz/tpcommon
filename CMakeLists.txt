cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project (tpcommon CXX)

set (tpcommon_VERSION_MAJOR 0)
set (tpcommon_VERSION_MINOR 1)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_definitions(-std=c++11)
add_definitions(-Wall)

install(DIRECTORY src/ DESTINATION include/tpcommon
        FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY / DESTINATION lib
        FILES_MATCHING PATTERN "*.so")

FIND_PACKAGE( OpenMP )
  if(OPENMP_FOUND)
     message("OPENMP FOUND")
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif()
 include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})


include_directories("${PROJECT_BINARY_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/catch")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/json")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/fakeit")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/lodepng")

set(app_SOURCES "a_main.cpp" )
file(GLOB_RECURSE lib_SOURCES "src/*.cpp")
file(GLOB_RECURSE app_TESTS "tests/*.cpp")

add_library(tpcommon SHARED ${lib_SOURCES})

add_executable(app_test ${app_TESTS} "${PROJECT_SOURCE_DIR}/thirdparty/lodepng/lodepng.cpp")
target_link_libraries(app_test tpcommon)
enable_testing()
add_test( app_test app_test )

