#ifndef RENDERABLE2D_HPP
#define RENDERABLE2D_HPP

// #include <graphics/Renderer2d.hpp>
// #include <graphics/buffers/IndexBuffer.hpp>
// #include <graphics/buffers/VertexArray.hpp>
// #include <graphics/Shader.hpp>
// #include <graphics/Texture.hpp>
#include <Maths.hpp>
#include <vector>
#include <glad/glad.h>

namespace GameEngine
{
    namespace graphics
    {
        class Renderer2d;
        class IndexBuffer;
        class VertexArray;
        class Shader;
        class Texture;
        
        class Renderable2d
        {
            public:
                glm::vec2 getSize() const;
                glm::vec3 Position() const;
                uint32_t Color() const;
                std::vector<glm::vec2> const & UV() const;
                GLuint TextureID() const;
                virtual  ~Renderable2d();

                virtual void submit(Renderer2d * renderer);
                void setColor(uint32_t color);
                void setColor(glm::vec4 color);

            protected:
                Renderable2d();
                Renderable2d(glm::vec2 size, glm::vec3 position, uint32_t color);
                glm::vec2 _size;
                glm::vec3 _position;
                uint32_t _color;
                std::vector<glm::vec2> _UV;
                Texture * _texture;
            
            private:
                void setUVDefaults();
                    
        };
    }
}

#endif