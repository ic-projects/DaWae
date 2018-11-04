cmake_minimum_required(VERSION 3.12)
project(arch2_2018_cw)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(arch2_2018_cw
        src/simulator.cpp
        linker.ld
        Makefile
        readme.md
        reflection.md src/Instruction.cpp src/Instruction.h)
