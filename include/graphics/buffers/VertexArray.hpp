#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <vector>
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

                void bind() ;
                void unbind() ;

            private:
                GLuint _arrayID;
                std::vector<Buffer *> _buffer; 
        };
    }
}

#endif