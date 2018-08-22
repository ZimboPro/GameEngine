#ifndef FONT_HPP
#define FONT_HPP
#include <glad/glad.h>
#include <graphics/Shader.hpp>
#include <string>
#include <map>

namespace GameEngine
{
    namespace graphics
    {
        struct Character {
            GLuint TextureID;
            glm::ivec2 Size;
            glm::ivec2 Bearing;
            GLuint Advance;
        };

        class Font
        {
            public:
                Font(std::string font, unsigned int size, unsigned int width, unsigned int height);
                ~Font();

                std::string FileName() const;
                unsigned int Size() const;

                std::map<GLchar, Character> Characters;
                Shader *_textShader;
                GLuint _VAO;
                GLuint _VBO;

            private:
                void Load();

                unsigned int _size;
                std::string _fileName;
        };
    }
}

#endif