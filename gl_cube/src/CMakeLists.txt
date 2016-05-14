cmake_minimum_required(VERSION 3.5.1)
set(GLFW "../deps/glfw") 
include_directories(${GLFW}/deps)
include_directories(${GLFW}/include)
file(GLOB SRC "*.c" "${GLFW}/deps/glad.c") 
add_executable(gl_cube ${SRC})
target_link_libraries(gl_cube ${CMAKE_BINARY_DIR}/deps/glfw/src/libglfw3.a)
target_link_libraries(gl_cube rt m dl X11 pthread Xrandr Xinerama Xxf86vm Xcursor)

