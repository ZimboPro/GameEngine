#include <graphics/buffers/IndexBuffer.hpp>

namespace GameEngine
{
    namespace graphics
    {
        IndexBuffer::IndexBuffer(GLushort * data, GLsizei count)
        {
            this->_count = count;

            glGenBuffers(1, &(this->_bufferID));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_bufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexBuffer::~IndexBuffer()
        {
            glDeleteBuffers(1, &this->_bufferID);
        }

        void IndexBuffer::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_bufferID);
        }

        void IndexBuffer::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
        }

        inline GLuint IndexBuffer::Count() const
        {
            return this->_count;
        }
    }
}