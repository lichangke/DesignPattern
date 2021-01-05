cmake_minimum_required(VERSION 3.15)
project(CommandPattern)

set(CMAKE_CXX_STANDARD 11)

add_executable(Client01 Client01.cpp CommandPattern.h)
add_executable(Client02 Client02.cpp CommandPattern.h)