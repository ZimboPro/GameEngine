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

                void bind() const;
                void unbind() const;
                const unsigned int Width() const;
                const unsigned int Height() const;
            private:
                std::string _path;
                GLuint _textureID;
                unsigned int _width;
                unsigned int _height;

                GLuint load();
        };
    }
}

#endif