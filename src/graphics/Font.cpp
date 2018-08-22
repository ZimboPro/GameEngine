#include <graphics/Font.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

namespace GameEngine
{
    namespace graphics
    {
        Font::Font(std::string font, unsigned int size, unsigned int width, unsigned int height)
        {
            this->_fileName = font;
            this->_size = size;

            glGenVertexArrays(1, &this->_VAO);
            glGenBuffers(1, &this->_VBO);
            glBindVertexArray(this->_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        Font::~Font()
        {
            this->Characters.clear();
        }

        std::string Font::FileName() const
        {
            return this->_fileName;
        }

        unsigned int Font::Size() const
        {
            return this->_size;
        }

        void Font::Load()
        {
            // First clear the previously loaded Characters
            this->Characters.clear();
            // Then initialize and load the FreeType library
            FT_Library ft;    
            if (FT_Init_FreeType(&ft)) // All functions return a value different than 0 whenever an error occurred
                std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            // Load font as face
            FT_Face face;
            if (FT_New_Face(ft, this->_fileName.c_str(), 0, &face))
                std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            // Set size to load glyphs as
            FT_Set_Pixel_Sizes(face, 0, this->_size);
            // Disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
            // Then for the first 128 ASCII characters, pre-load/compile their characters and store them
            for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
            {
                // Load character glyph 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                // Generate texture
                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                    );
                // Set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
                // Now store character for later use
                Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    face->glyph->advance.x
                };
                Characters.insert(std::pair<GLchar, Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
            // Destroy FreeType once we're finished
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
        }
    }
}