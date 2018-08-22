cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(GameEngine)

set(NAME GameEngine)


set(FETCHCONTENT_QUIET OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++") 
endif()

include(FetchContent)

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
    glfw
    URL https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

include_directories(${glfw_SOURCE_DIR}/include)

FetchContent_Declare(
    std_image
    GIT_REPOSITORY https://github.com/jschmidt42/stb-cmake.git
)

FetchContent_GetProperties(std_image)

if(NOT std_image_POPULATED)
  FetchContent_Populate(std_image)
endif()

include_directories(${std_image_SOURCE_DIR})

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/0.9.7.0.zip
)

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
endif()

include_directories(${glm_SOURCE_DIR})

FetchContent_Declare(
    freetype
    GIT_REPOSITORY git://git.sv.nongnu.org/freetype/freetype2.git
)

FetchContent_GetProperties(freetype)

if(NOT freetype_POPULATED)
    FetchContent_Populate(freetype)
    set(FT_WITH_PNG ON CACHE BOOL "" FORCE)
    set(FT_WITH_ZLIB ON CACHE BOOL "" FORCE)
    add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()

include_directories(${freetype_SOURCE_DIR})

FetchContent_Declare(
    assimp
    URL https://github.com/assimp/assimp/archive/v4.1.0.zip
)

FetchContent_GetProperties(assimp)

if(NOT assimp_POPULATED)
  FetchContent_Populate(assimp)
  set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)

  add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
endif()

include_directories(
    ${assimp_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/include
)

# add_library(
add_executable(
    ${NAME}
    main.cpp
    src/graphics/Window.cpp
    src/graphics/Shader.cpp
    src/graphics/Renderable2d.cpp
    src/graphics/Renderer2d.cpp
    src/graphics/Batch2dRenderer.cpp
    src/graphics/Sprite.cpp
    src/graphics/Texture.cpp
    src/graphics/Label.cpp
    src/graphics/Font.cpp
    src/graphics/FontManager.cpp

    src/utils/FileUtils.cpp
    src/utils/Times.cpp
    
    src/graphics/buffers/Buffer.cpp
    src/graphics/buffers/IndexBuffer.cpp
    src/graphics/buffers/VertexArray.cpp

    src/graphics/layers/Layer.cpp
    src/graphics/layers/TileLayer.cpp
    src/graphics/layers/Group.cpp
    
    ${glad_SOURCE_DIR}/src/glad.c
)

find_package(OpenGL REQUIRED)

target_link_libraries(${NAME} glfw freetype assimp ${OPENGL_gl_LIBRARY})

if (OPENGL_GLU_FOUND)
    target_link_libraries(${NAME} ${OPENGL_glu_LIBRARY})
endif()