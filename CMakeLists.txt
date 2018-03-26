cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project (tpcommon CXX)

set (tpcommon_VERSION_MAJOR 0)
set (tpcommon_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -DVER=${gcdapi_VERSION_MAJOR}.${gcdapi_VERSION_MINOR}")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

FIND_PACKAGE( OpenMP )
  if(OPENMP_FOUND)
     message("OPENMP FOUND")
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif()
 include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})


include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/catch")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/json")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/fakeit")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/lodepng")

set(app_SOURCES "${PROJECT_SOURCE_DIR}/a_main.cpp" )
file(GLOB_RECURSE lib_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE app_TESTS "${PROJECT_SOURCE_DIR}/tests/*.cpp")

add_library(tpcommon SHARED ${lib_SOURCES} "${PROJECT_SOURCE_DIR}/thirdparty/lodepng/lodepng.cpp")

add_executable(app_test EXCLUDE_FROM_ALL ${app_TESTS} "${PROJECT_SOURCE_DIR}/thirdparty/lodepng/lodepng.cpp")
target_link_libraries(app_test tpcommon)


install(TARGETS tpcommon DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/tpcommon
        FILES_MATCHING PATTERN "*.hpp")


enable_testing()
add_test( app_test app_test
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
         )
add_custom_target(check COMMAND ${CMAKE_BINARY_DIR}/app_test
                  DEPENDS app_test
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                  )


SET(CPACK_PACKAGE_VERSION_MAJOR ${mhttp_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${mhttp_VERSION_MINOR})
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_GENERATOR "DEB" "TGZ")

SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tadeusz Puźniakowski")
INCLUDE(CPack)


 
# To use this:
# make package



