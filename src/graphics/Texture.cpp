#include <graphics/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>


namespace GameEngine
{
    namespace graphics
    {
        Texture::Texture(const std::string & path)
        {
            this->_path = path;
            load();
        }

        Texture::~Texture()
        {}

        void Texture::bind() 
        {
            glBindTexture(GL_TEXTURE_2D, this->_textureID);
        }

        void Texture::unbind() 
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        unsigned int Texture::Width() 
        {
            return this->_width;
        }

        unsigned int Texture::Height() 
        {
            return this->_height;
        }

        void Texture::load()
        {
            glGenTextures(1, &this->_textureID);
            glBindTexture(GL_TEXTURE_2D, this->_textureID);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            unsigned char * data = stbi_load(this->_path.c_str(), &this->_width, &this->_height, &this->_channel, 0);
            
            if (!data)
                std::cout << "Error loading image" << std::endl;
            else
            {
                if(this->_channel == 3)
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                else
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }

            stbi_image_free(data);
        }

        GLuint Texture::ID() 
        {
            return this->_textureID;
        }
    }
}