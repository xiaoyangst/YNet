cmake_minimum_required(VERSION 3.16)
project(YNetProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(YNet/base)
include_directories(YNet/net)

add_subdirectory(Test)
add_subdirectory(YNet)

add_executable(YNetProject main.cpp)

