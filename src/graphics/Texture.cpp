#include <graphics/Texture.hpp>
#include <utils/ImageLoad.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Texture::Texture(const std::string & path)
        {
            this->_path = path;
            this->_textureID = load();
        }

        Texture::~Texture()
        {}

        void Texture::bind() const
        {
            glBindTexture(GL_TEXTURE_2D, this->_textureID);
        }

        void Texture::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        inline const unsigned int Texture::Width() const
        {
            return this->_width;
        }

        inline const unsigned int Texture::Height() const
        {
            return this->_height;
        }

        GLuint Texture::load()
        {
            BYTE * pixels = load_image(this->_path.c_str(), this->_width, this->_height);

            GLuint result;
            glGenTextures(1, &result);
            glBindTexture(GL_TEXTURE_2D, result);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(this->_width), static_cast<GLsizei>(this->_height),0 , GL_BGR, GL_UNSIGNED_BYTE, pixels);
            glBindTexture(GL_TEXTURE_2D, 0);
            return result;
        }

        inline const GLuint Texture::ID() const
        {
            return this->_textureID;
        }
    }
}