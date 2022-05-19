cmake_minimum_required(VERSION 3.3)
project(Ytest CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Za")
endif()

add_executable(y_test main.cpp)
set_target_properties(y_test PROPERTIES OUTPUT_NAME "y_test")
set_target_properties(y_test PROPERTIES PREFIX "")