cmake_minimum_required(VERSION 3.26)
project(libftmesh_cpp)


set(CMAKE_CXX_STANDARD 20)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.71.0 REQUIRED)

include_directories("/usr/include/c++/13")

add_library(libftmesh_cpp ftmesh.cpp
        example/main.cpp
        example/main.h)
