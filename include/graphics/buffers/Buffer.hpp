#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <glad/glad.h>

namespace GameEngine
{
    namespace graphics
    {
        class Buffer
        {
            public:
                Buffer(GLfloat * data, GLsizei count, GLuint componentCount);
                ~Buffer();
                void bind() ;
                void unbind() ;

                GLuint ComponentCount() const; 
            private:
                GLuint _bufferID;
                GLuint _componentCount;
        };
    }
}

#endif