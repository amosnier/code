cmake_minimum_required(VERSION 3.5.1)
project (gl_cube)
set(GLFW "deps/glfw")
add_subdirectory(${GLFW})
include_directories(${GLFW}/deps ${GLFW}/include)
file(GLOB SRC "src/*.c" "${GLFW}/deps/glad.c")
add_executable(gl_cube ${SRC})
target_link_libraries(gl_cube glfw ${GLFW_LIBRARIES})

