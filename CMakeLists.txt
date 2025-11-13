cmake_minimum_required(VERSION 3.11)
project(setup)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Output directory ####
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### GLFW ####
add_subdirectory(lib/glfw)

# GLFW include directory
set(GLFW_INCS "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include")

#### GLAD ####
add_library(glad
    lib/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
)

#### Source files ####
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(main ${SOURCES})

# Add include dirs for executable
target_include_directories(main PRIVATE
    ${GLFW_INCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
)

# Link libraries
target_link_libraries(main PRIVATE glfw glad)

#### Copy resources ####
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)