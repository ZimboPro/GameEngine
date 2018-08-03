#include <graphics/buffers/VertexArray.hpp>

namespace GameEngine
{
    namespace graphics
    {
        VertexArray::VertexArray()
        {
            glGenVertexArrays(1, &this->_arrayID);
        }

        VertexArray::~VertexArray()
        {
            for (int i = 0; i < this->_buffer.size(); i++)
            {
                delete this->_buffer[i];
            }
            this->_buffer.clear(); 
        }

        void VertexArray::addBuffer(Buffer * buffer, GLuint index)
        {
            bind();

            buffer->bind();
            glEnableVertexArrayAttrib(index);
            glVertexAttribPointer(index, buffer->ComponentCount(),GL_FLOAT, GL_FALSE, 0, 0);

            this->_buffer.push_back(buffer);

            buffer->unbind();
            unbind();
        }

        void VertexArray::bind() const
        {
            glBindVertexArray(this->_arrayID);
        }

        void VertexArray::unbind() const
        {
            glBindVertexArray(0); 
        }
    }
}