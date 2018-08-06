#ifndef RENDERABLE2D_HPP
#define RENDERABLE2D_HPP

#include <graphics/buffers/Buffer.hpp>
#include <graphics/buffers/IndexBuffer.hpp>
#include <graphics/buffers/VertexArray.hpp>
#include <graphics/Shader.hpp>
#include <Maths.hpp>

namespace GameEngine
{
    namespace graphics
    {
        struct VertexData
        {
            glm::vec3 vertex;
            glm::vec4 color;
        };

        class Renderable2d
        {
            public:
                const glm::vec2 getSize() const;
                const glm::vec3 Position() const;
                const glm::vec4 Color() const;

            protected:
                Renderable2d(glm::vec2 size, glm::vec3 position, glm::vec4 color);
                virtual  ~Renderable2d();
                glm::vec2 _size;
                glm::vec3 _position; 
                glm::vec4 _color;

                    
        };
    }
}

#endif