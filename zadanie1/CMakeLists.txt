cmake_minimum_required(VERSION 3.22)
project(zadanie1)

set(CMAKE_CXX_STANDARD 14)

add_executable(zadanie1 main.cpp Branch_Bound.cpp Branch_Bound.h Brute_force.cpp Brute_force.h
        M_Generator.cpp M_Generator.h matrix.cpp matrix.h Test.cpp Test.h)
