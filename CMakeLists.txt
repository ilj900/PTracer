cmake_minimum_required(VERSION 3.14)
project(PTracer)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(glad)

include_directories(include
                    glad/include
                    ecs)
link_directories(libs)

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
        include/light.h
            include/linmath.h
            include/randomizer.h
            include/draw_manager.h
            src/draw_manager.cpp
            include/matrix2.h
            include/constants.h
            include/matrix3.h
            include/matrix4.h
            include/transformation.h src/light_system.cpp include/light_system.h include/quaternions.h)

add_executable(PTracer ${SOURCE})

target_link_libraries(PTracer glfw3 glad)