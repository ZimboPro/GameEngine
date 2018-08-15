#include <graphics/buffers/VertexArray.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
            for (size_t i = 0; i < this->_buffer.size(); i++)
            {
                delete this->_buffer[i];
            }
            this->_buffer.clear();
            glDeleteVertexArrays(1, &this->_arrayID);
        }

        void VertexArray::addBuffer(Buffer * buffer, GLuint index)
        {
            bind();

            buffer->bind();
            glEnableVertexArrayAttrib(this->_arrayID ,index);
            glVertexAttribPointer(index, buffer->ComponentCount(),GL_FLOAT, GL_FALSE, 0, 0);

            buffer->unbind();
            unbind();

            this->_buffer.push_back(buffer);
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