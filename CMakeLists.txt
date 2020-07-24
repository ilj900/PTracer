cmake_minimum_required(VERSION 3.16)
project(PTracer)

set(SOURCE  src/main.cpp
            include/utils.h
            include/vector2.h
            include/vector3.h
            include/vector4.h
            include/triangle.h
            include/sphere.h)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(PTracer ${SOURCE})