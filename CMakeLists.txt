cmake_minimum_required(VERSION 3.16)
project(PTracer)

set(SOURCE  src/main.cpp
            src/stb_image_write.cpp
            include/utils.h
            include/vector3.h
            include/stb_image_write.h
            include/vector4.h
            include/triangle.h
            include/sphere.h
            include/ray.h
            include/plane.h
            include/intersections.h)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(PTracer ${SOURCE})