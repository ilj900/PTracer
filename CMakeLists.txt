cmake_minimum_required(VERSION 3.14)
project(PTracer)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

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
            include/timing.h
            include/plane.h
            include/camera.h
            include/point_light.h
            include/linmath.h
            include/randomizer.h)

add_executable(PTracer ${SOURCE})