#ifndef VERTEXDATA_HPP
#define VERTEXDATA_HPP

#include <Maths.hpp>

namespace GameEngine
{
    namespace graphics
    {
        typedef struct VertexDatas
        {
            glm::vec3 vertex;
            glm::vec2 uv;
            float tid;
            uint32_t color;
        }               VertexData;
    }
}

#endif