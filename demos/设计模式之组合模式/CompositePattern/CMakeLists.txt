cmake_minimum_required(VERSION 3.15)
project(CompositePattern01)

set(CMAKE_CXX_STANDARD 11)

add_executable(Client01 Client01.cpp CompositePattern01.h)
add_executable(Client02 Client02.cpp CompositePattern02.h)