cmake_minimum_required(VERSION 3.15)
project(StatePattern)

set(CMAKE_CXX_STANDARD 11)

add_executable(client01 client01.cpp StatePattern01.h)
add_executable(client02 client02.cpp StatePattern02.h)