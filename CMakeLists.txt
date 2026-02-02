cmake_minimum_required(VERSION 3.11)
project(HonoursProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(lib/glfw)

set(GLFW_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include"
)

add_library(glad
    "lib/glad/src/glad.c"
 "src/sim_env.hpp")

target_include_directories(glad PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include"
)

set(GLM_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm"
)

set(SOURCES
    "src/main.cpp"
    "src/shader.cpp"
    "src/baseGrid.cpp"
)

set(HEADERS
    "src/Shader.h"
    "src/baseGrid.hpp"
)

add_executable(main ${SOURCES} "src/main.cpp")

target_include_directories(main PRIVATE
    ${GLFW_INCLUDES}
    ${GLM_INCLUDES}
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(main PRIVATE glfw glad)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:main>/res"
)