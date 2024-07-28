cmake_minimum_required(VERSION 3.16)
project(YNet)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/base)
include_directories(include/net)
aux_source_directory(src SRC_LIST)

add_subdirectory(src)

