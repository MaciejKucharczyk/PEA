cmake_minimum_required(VERSION 3.24)
project(zadanie3)

set(CMAKE_CXX_STANDARD 14)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
# set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(zadanie3 main.cpp Matrix.cpp Matrix.h Algorithm.cpp Algorithm.h)
