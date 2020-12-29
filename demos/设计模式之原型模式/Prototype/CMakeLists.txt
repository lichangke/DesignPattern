cmake_minimum_required(VERSION 3.15)
project(Prototype)

set(CMAKE_CXX_STANDARD 11)

add_executable(Client01 Client01.cpp Prototype.h)
add_executable(Client02 Client02.cpp Prototype.h)