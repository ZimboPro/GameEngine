#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glad/glad.h>

namespace GameEngine
{
    namespace graphics
    {
        class Texture
        {
            public:
                Texture(const std::string& path);
                ~Texture();

                void bind() ;
                void unbind() ;
                unsigned int Width() ;
                unsigned int Height() ;
                GLuint ID() ;
            private:
                std::string _path;
                GLuint _textureID;
                int _width;
                int _height;
                int _channel;

                void load();
        };
    }
}

#endif