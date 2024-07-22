cmake_minimum_required(VERSION 3.27)
project(QuineEmu)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)
include_directories(vm)

add_executable(QuineEmu
        main.cpp
        vm/vm.hpp
        vm/vm.cpp)
