cmake_minimum_required(VERSION 3.26)
project(simple_perf)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++-13)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.71.0 REQUIRED)

include_directories("/usr/include/c++/13")

add_library(libftmesh_cpp ../ftmesh.cpp ../ftmesh.h)

add_executable(main main.cpp main.h)

target_link_libraries(main PRIVATE libftmesh_cpp)