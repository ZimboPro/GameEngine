#include <graphics/buffers/Buffer.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Buffer::Buffer(GLfloat * data, GLsizei count, GLuint componentCount)
        {
            this->_componentCount = componentCount;

            glGenBuffers(1, &(this->_bufferID));
            glBindBuffer(GL_ARRAY_BUFFER, this->_bufferID);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        Buffer::~Buffer()
        {
            glDeleteBuffers(1, &this->_bufferID);
        }

        void Buffer::bind() 
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->_bufferID);
        }

        void Buffer::unbind() 
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        GLuint Buffer::ComponentCount() const
        {
            return this->_componentCount;
        }

    }
}