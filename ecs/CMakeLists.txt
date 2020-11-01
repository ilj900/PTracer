SET(HEADERS
        entity.h)

SET(SOURCE
        entity.cpp)

add_library(ECS STATIC ${HEADERS} ${SOURCE})