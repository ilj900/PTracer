include_directories(include)

SET(HEADERS
		include/glad/glad.h
		include/KHR/khrplatform.h)

SET(SOURCE
		src/glad.c)

add_library(glad STATIC ${HEADERS} ${SOURCE})