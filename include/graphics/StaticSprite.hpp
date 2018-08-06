#ifndef STATICSPRITE_HPP
#define STATICSPRITE_HPP

#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class StaticSprite : public Renderable2d
        {
            public:
                StaticSprite(float x, float y, float width, float height, glm::vec4  color, Shader & shader);
                ~StaticSprite();
                const VertexArray* getVAO() const;
                const IndexBuffer* getIBO() const;
                const Shader & getShader() const;

            private:
                Shader _shader;
                VertexArray* _vertexArray;
                IndexBuffer* _indexBuffer;  
        };
    }
}

#endif