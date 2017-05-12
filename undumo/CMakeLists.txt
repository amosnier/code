cmake_minimum_required(VERSION 3.5.2)

project(undumo)

find_program(CODE_TO_STRING xxd)

include_directories(src)
include_directories(contrib/glad/include)
include_directories (${CMAKE_BINARY_DIR})

file(GLOB SRC "src/*.cpp")
file(GLOB GLAD_SRC "contrib/glad/src/*.c")
file(GLOB GLSL_SRC "glsl/*.glsl")

# Generate GLSL header files
foreach(INPUT_FILE ${GLSL_SRC})
  get_filename_component(INPUT_FILENAME ${INPUT_FILE} NAME)
  set(OUTPUT_FILE ${INPUT_FILENAME}.h)
  add_custom_command(
    OUTPUT ${OUTPUT_FILE}
    COMMAND ${CMAKE_COMMAND} -E copy ${INPUT_FILE} ${CMAKE_BINARY_DIR}
    COMMAND ${CODE_TO_STRING} -i ${INPUT_FILENAME} ${OUTPUT_FILE}
    COMMENT "Creating ${OUTPUT_FILE} from ${INPUT_FILENAME}"
    DEPENDS ${INPUT_FILE})
  list(APPEND GENERATED_HEADERS ${OUTPUT_FILE})
endforeach()

add_executable(${CMAKE_PROJECT_NAME} ${SRC} ${GLAD_SRC} ${GENERATED_HEADERS})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(contrib/glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
