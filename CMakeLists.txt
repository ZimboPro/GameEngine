cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(GameEngine)

set(NAME GameEngine)

set(CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include(FetchContent)

FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

include_directories(${glfw_SOURCE_DIR}/include)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG origin/c
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
  FetchContent_Populate(glad)
endif()

include_directories(${glad_SOURCE_DIR}/include)


add_executable(
    ${NAME}
    src/graphics/Window.cpp
)


find_package(OpenGL REQUIRED)

target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY})

if (OPENGL_GLU_FOUND)
    target_link_libraries(${NAME} ${OPENGL_glu_LIBRARY})
endif()