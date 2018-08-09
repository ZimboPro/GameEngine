#ifndef RENDERABLE2D_HPP
#define RENDERABLE2D_HPP

#include <graphics/buffers/Buffer.hpp>
#include <graphics/buffers/IndexBuffer.hpp>
#include <graphics/buffers/VertexArray.hpp>
#include <graphics/Shader.hpp>
#include <graphics/Renderer2d.hpp>
#include <graphics/Texture.hpp>
#include <Maths.hpp>

namespace GameEngine
{
    namespace graphics
    {
        struct VertexData
        {
            glm::vec3 vertex;
            glm::vec2 uv;
            float tid;
            uint32_t color;
        };

        class Renderable2d
        {
            public:
                const glm::vec2 getSize() const;
                const glm::vec3 Position() const;
                const glm::vec4 Color() const;
                const std::vector<glm::vec2> & UV() const;
                const GLuint TextureID() const;
                virtual  ~Renderable2d();

                virtual void submit(Renderer2d * renderer) const;

            protected:
                Renderable2d();
                Renderable2d(glm::vec2 size, glm::vec3 position, glm::vec4 color);
                glm::vec2 _size;
                glm::vec3 _position; 
                glm::vec4 _color;
                std::vector<glm::vec2> _UV;
                Texture * _texture;
            
            private:
                void setUVDefaults();
                    
        };
    }
}

#endif