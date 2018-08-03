#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Renderable2d::Renderable2d(glm::vec2 size, glm::vec3 position, glm::vec4 color, Shader &shader) : _shader(shader)
        {
            this->_position = position;
            this->_size = size;
            this->_color = color;

            this->_vertexArray = new VertexArray();

            GLfloat vertices[] = 
            {
                0, 0, 0,
                0, size.x, 0,
                size.x, size.y, 0,
                size.x, size.y, 0
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
        Renderable2d::~Renderable2d()
        {
            delete this->_vertexArray;
            delete this->_indexBuffer ;
        }

        inline  const glm::vec3 Renderable2d::Position() const
        {
            return (this->_position);
        }

        inline const glm::vec2 Renderable2d::getSize() const
        {
            return (this->_size);
        }

        inline const glm::vec4 Renderable2d::Color() const
        {
            return (this->_color);
        }

        inline const VertexArray* Renderable2d::getVAO() const
        {
            return this->_vertexArray;
        }

        inline const IndexBuffer* Renderable2d::getIBO() const
        {
            return this->_indexBuffer;
        }

        inline const Shader & Renderable2d::getShader() const
        {
            return (this->_shader);
        }

    }
}