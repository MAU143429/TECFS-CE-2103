cmake_minimum_required(VERSION 3.19)
project(TEC_FS)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(TEC_FS main.cpp src/UtilJSON/JSON_Management.h src/Objects/TypeMessage.h src/Socket/Server.h src/Algorithms/HuffmanCompression.h src/Objects/Huffman_pair.h)