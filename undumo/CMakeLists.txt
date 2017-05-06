cmake_minimum_required(VERSION 3.5.2)

project(undumo)

include_directories(src)
include_directories(contrib/glad/include)

file(GLOB SRC "src/*.cpp")
file(GLOB GLAD_SRC "contrib/glad/src/*.c")

add_executable(${CMAKE_PROJECT_NAME} ${SRC} ${GLAD_SRC})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(contrib/glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
