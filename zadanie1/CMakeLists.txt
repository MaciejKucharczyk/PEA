cmake_minimum_required(VERSION 3.22)
project(pea)

set(CMAKE_CXX_STANDARD 14)

add_executable(pea main.cpp matrix.cpp matrix.h M_Generator.cpp M_Generator.h Brute_force.cpp Brute_force.h Test.cpp Test.h Branch_Bound.cpp Branch_Bound.h)
