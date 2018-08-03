#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <vector>
#include <glad/glad.h>
#include <graphics/buffers/Buffer.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class VertexArray
        {
            public:
                VertexArray();
                ~VertexArray();
                void addBuffer(Buffer * buffer, GLuint index);

                void bind() const;
                void unbind() const;

            private:
                GLuint _arrayID;
                std::vector<Buffer *> _buffer; 
        };
    }
}

#endif