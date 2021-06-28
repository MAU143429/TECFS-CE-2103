cmake_minimum_required(VERSION 3.19)
project(Disk_Node)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(Disk_Node main.cpp src/Socket/Client.h)