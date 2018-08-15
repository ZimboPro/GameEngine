#include <graphics/StaticSprite.hpp>

namespace GameEngine
{
    namespace graphics
    {
        StaticSprite::StaticSprite(float x, float y, float width, float height, glm::vec4  color, Shader & shader) :
                 Renderable2d(glm::vec2(width, height) ,glm::vec3(x, y, 0),  0xffffffff) , _shader(shader)
        {
             this->_vertexArray = new VertexArray();

            GLfloat vertices[] = 
            {
                0, 0, 0,
                0, height, 0,
                width, height, 0,
                width, 0, 0
            };

            GLfloat col[] = 
            {
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w
            };

            this->_vertexArray->addBuffer(new Buffer(vertices, 4 * 3,  3), 0);
            this->_vertexArray->addBuffer(new Buffer(col, 4 * 4,  4), 1);

            GLushort indices[] = {0,1,2,2,3,0};
            this->_indexBuffer = new IndexBuffer(indices, 6);
        }

        StaticSprite::~StaticSprite()
        {
            delete this->_indexBuffer;
            delete this->_vertexArray;
        }

        inline const VertexArray* StaticSprite::getVAO() const
        {
            return this->_vertexArray;
        }

        inline const IndexBuffer* StaticSprite::getIBO() const
        {
            return this->_indexBuffer;
        }

        inline const Shader & StaticSprite::getShader() const
        {
            return (this->_shader);
        }
    }
}