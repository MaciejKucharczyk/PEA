cmake_minimum_required(VERSION 3.22)
project(zadanie2)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(zadanie2 main.cpp matrix.h matrix.cpp Tabu.cpp Tabu.h Wyzarzanie.cpp Wyzarzanie.h)
