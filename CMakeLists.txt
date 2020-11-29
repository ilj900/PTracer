cmake_minimum_required(VERSION 3.14)
project(PTracer)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(glad)

include_directories(include
                    glad/include
                    ecs)

link_directories(libs)

set(VARIOUS
        src/main.cpp
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
        include/transformation.h
        include/quaternions.h)

set(SYSTEMS
        systems/light_system.h
        systems/light_system.cpp)

set(ECS
        ecs/entity.h
        ecs/component_array.h
        ecs/entity_manager.h
        ecs/system.h
        ecs/component_manager.h
        ecs/director.h
        ecs/system_manager.h)

set(SOURCE
        ${VARIOUS}
        ${SYSTEMS}
        ${ECS})

add_executable(PTracer ${SOURCE})

target_link_libraries(PTracer glfw3 glad)