#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <glad/glad.h>

namespace GameEngine
{
    namespace graphics
    {
        class InderBuffer
        {
            public:
                InderBuffer(GLushort * data, GLsizei count);
                void bind() const;
                void unbind() const;

                GLuint Count() const; 
            private:
                GLuint _bufferID;
                GLuint _count;
        };
    }
}

#endif