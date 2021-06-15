cmake_minimum_required(VERSION 3.19)
project(TEC_FS)

set(CMAKE_CXX_STANDARD 14)

add_executable(TEC_FS main.cpp src/UtilJSON/JSON_Management.h src/Objects/TypeMessage.h src/Socket/Server.cpp src/Socket/Server.h src/Algorithms/HuffmanCompression.h)