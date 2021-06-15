cmake_minimum_required(VERSION 3.19)
project(TEC_FS)

set(CMAKE_CXX_STANDARD 14)

add_executable(TEC_FS main.cpp src/DataStructures/SimplyList.h src/UtilJSON/JSON_Management.h src/Objects/TypeMessage.h src/Algorithms/HuffmanCompression.h)