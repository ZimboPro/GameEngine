cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(GameEngine)

set(NAME GameEngine)

set(CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

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

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/0.9.9.0.zip
)

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

include_directories(${glm_SOURCE_DIR})

include_directories(include)

add_library(
    ${NAME}
    src/graphics/Window.cpp
    src/graphics/Shader.cpp
    src/graphics/Renderable2d.cpp
    src/graphics/SimpleRenderer2d.cpp
    src/graphics/Batch2dRenderer.cpp
    src/graphics/StaticSprite.cpp
    src/graphics/Sprite.cpp

    src/utils/FileUtils.cpp
    
    src/graphics/buffers/Buffer.cpp
    src/graphics/buffers/IndexBuffer.cpp
    src/graphics/buffers/VertexArray.cpp
    
    ${glad_SOURCE_DIR}/src/glad.c
)


find_package(OpenGL REQUIRED)

target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY})

if (OPENGL_GLU_FOUND)
    target_link_libraries(${NAME} ${OPENGL_glu_LIBRARY})
endif()