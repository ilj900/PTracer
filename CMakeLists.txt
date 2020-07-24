cmake_minimum_required(VERSION 3.16)
project(PTracer)

set(SOURCE  src/main.cpp
            include/utils.h
            include/vector3.h)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(PTracer ${SOURCE})