cmake_minimum_required(VERSION 3.14)
project(PTracer)

set(SOURCE  src/main.cpp
            src/stb_image_write.cpp
            include/utils.h
            include/vector2.h
            include/vector3.h
            include/vector4.h
            include/image.h
            include/stb_image_write.h
            include/shape.h
            include/triangle.h
            include/sphere.h
            include/ray.h
            include/plane.h
            include/camera.h
            include/point_light.h
            include/linmath.h
            include/randomizer.h)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(PTracer ${SOURCE})