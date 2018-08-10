cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(GameEngine)

set(NAME GameEngine)

set(CXX_STANDARD 17)

if (APPLE)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -stdlib=libc++")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif()

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
    freeimage
    GIT_REPOSITORY https://github.com/Kanma/FreeImage.git
)

FetchContent_GetProperties(freeimage)

if(NOT freeimage_POPULATED)
    FetchContent_Populate(freeimage)
    add_subdirectory(${freeimage_SOURCE_DIR} ${freeimage_BINARY_DIR})
endif()

include_directories(${freeimage_SOURCE_DIR}/include)

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
endif()

include_directories(${glm_SOURCE_DIR})

# FetchContent_Declare(
#     freetype
#     GIT_REPOSITORY https://github.com/rougier/freetype-gl.git
# )

# FetchContent_GetProperties(freetype)

# if(NOT freetype_POPULATED)
#     FetchContent_Populate(freetype)
#     add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
# endif()

# include_directories(${freetype_SOURCE_DIR}/include)

include_directories(include)

add_library(
    ${NAME}
    src/graphics/Window.cpp
    src/graphics/Shader.cpp
    src/graphics/Renderable2d.cpp
    src/graphics/Renderer2d.cpp
    src/graphics/SimpleRenderer2d.cpp
    src/graphics/Batch2dRenderer.cpp
    src/graphics/StaticSprite.cpp
    src/graphics/Sprite.cpp
    src/graphics/Texture.cpp

    src/utils/FileUtils.cpp
    src/utils/Times.cpp
    src/utils/ImageLoad.cpp
    
    src/graphics/buffers/Buffer.cpp
    src/graphics/buffers/IndexBuffer.cpp
    src/graphics/buffers/VertexArray.cpp

    src/graphics/layers/Layer.cpp
    src/graphics/layers/TileLayer.cpp
    src/graphics/layers/Group.cpp
    
    ${glad_SOURCE_DIR}/src/glad.c
)

target_link_libraries(${NAME} glfw)
target_link_libraries(${NAME} freeimage)

find_package(OpenGL REQUIRED)
target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY})

if (OPENGL_GLU_FOUND)
    target_link_libraries(${NAME} ${OPENGL_glu_LIBRARY})
endif()

find_library(freetype REQUIRED)
target_link_libraries(${NAME} ${FREETYPE_LIBRARY})