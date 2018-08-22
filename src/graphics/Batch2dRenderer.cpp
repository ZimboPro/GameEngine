#include <graphics/buffers/IndexBuffer.hpp>
#include <graphics/Batch2dRenderer.hpp>
#include <graphics/Renderable2d.hpp>
#include <graphics/Font.hpp>
#include <string>


namespace GameEngine
{
    namespace graphics
    {
        Batch2dRenderer::Batch2dRenderer()
        {
            Init();
        }

        Batch2dRenderer::~Batch2dRenderer()
        {
            delete this->_ibo;
            glDeleteBuffers(1, &this->_vbo);
        }

        void Batch2dRenderer::Init()
        {
            glGenVertexArrays(1, &this->_vao);

            glBindVertexArray(this->_vao);

            glGenBuffers(1, &this->_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
            glBufferData(GL_ARRAY_BUFFER, RENDER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
            
            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_UV_INDEX);
            glEnableVertexAttribArray(SHADER_TID_INDEX);
            glEnableVertexAttribArray(SHADER_COLOR_INDEX);
            
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, static_cast< GLvoid *>(0));
            glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, reinterpret_cast< void *>(offsetof(VertexData, uv)));
            glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, reinterpret_cast< void *>(offsetof(VertexData, tid)));
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDER_VERTEX_SIZE, reinterpret_cast< void *>(offsetof(VertexData, color)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            GLushort indices[RENDER_INDICES_SIZE];

            int offset = 0;
            for (int i = 0; i < RENDER_INDICES_SIZE; i += 6)
            {
                indices[i] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }

            this->_ibo = new IndexBuffer(indices, RENDER_INDICES_SIZE);
            glBindVertexArray(0);
        }

        void Batch2dRenderer::begin()
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
            this->_buffer =  reinterpret_cast<VertexData *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        }

        void Batch2dRenderer::submit(Renderable2d * renderable)
        {
            glm::vec3 positon = renderable->Position();
            glm::vec2 size = renderable->getSize();
            uint32_t c = renderable->Color();
            const std::vector<glm::vec2>& uv = renderable->UV();
            GLuint tid = renderable->TextureID();

            float ts = 0.0f;
            if (tid > 0)
            {
                bool found = false;
                for (size_t i = 0; i < this->_textureSlots.size(); i++)
                {
                    if (this->_textureSlots[i] == tid)
                    {
                        ts = static_cast<float>(i + 1);
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    if (this->_textureSlots.size() >= 32)
                    {
                        end();
                        flush();
                        begin();
                    }
                    this->_textureSlots.push_back(tid);
                    ts = static_cast<float>(this->_textureSlots.size());
                }
            }

            this->_buffer->vertex = glm::vec3(*(this->_transformationBack) * glm::vec4(positon, 1.0f));
            this->_buffer->color = c;
            this->_buffer->uv = uv[0];
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_buffer->vertex = glm::vec3(*(this->_transformationBack) * glm::vec4(positon.x, positon.y + size.y, positon.z, 1.0f));
            this->_buffer->color = c;
            this->_buffer->uv = uv[1];
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_buffer->vertex = glm::vec3(*(this->_transformationBack) * glm::vec4(positon.x + size.x, positon.y + size.y, positon.z, 1.0f));
            this->_buffer->uv = uv[2];
            this->_buffer->color = c;
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_buffer->vertex = glm::vec3(*(this->_transformationBack) * glm::vec4(positon.x + size.x, positon.y, positon.z, 1.0f));
            this->_buffer->uv = uv[3];
            this->_buffer->color = c;
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_count += 6;
        }

        void Batch2dRenderer::end()
        {
            //glBindBuffer(GL_ARRAY_BUFFER, 0);
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }

        void Batch2dRenderer::flush()
        {
            for (size_t i = 0; i < this->_textureSlots.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, this->_textureSlots[i]);
            }

            glBindVertexArray(this->_vao);
            this->_ibo->bind();

            glDrawElements(GL_TRIANGLES, this->_count, GL_UNSIGNED_SHORT, NULL);

            this->_ibo->unbind();
            glBindVertexArray(0);

            this->_count = 0;
        }

        void Batch2dRenderer::drawString(const std::string & text, const glm::vec3 & position, const Font &font, const uint32_t & color)
        {
            font._textShader->enable();

            glm::vec3 col(1.0f);
            col.x = (color % 256) / 255.0f;
            col.y = ((color >> 8) % 256) / 255.0f;
            col.z = ((color >> 16) % 256) / 255.0f;

            font._textShader->setVec3("textColor", col);
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(font._VAO);
            float x = position.x;

            // Iterate through all characters
            
            for (size_t i = 0; i < text.size(); i++)
            {
                GLchar c = text.c_str()[i];
                const Character ch = font.Characters.at(c);

                GLfloat xpos = position.x + ch.Bearing.x * font.Size();
                GLfloat ypos = position.y + (font.Characters.at('H').Bearing.y - ch.Bearing.y) * font.Size();

                GLfloat w = ch.Size.x * font.Size();
                GLfloat h = ch.Size.y * font.Size();
                // Update VBO for each character
                GLfloat vertices[6][4] = {
                    { xpos,     ypos + h,   0.0, 1.0 },
                    { xpos + w, ypos,       1.0, 0.0 },
                    { xpos,     ypos,       0.0, 0.0 },

                    { xpos,     ypos + h,   0.0, 1.0 },
                    { xpos + w, ypos + h,   1.0, 1.0 },
                    { xpos + w, ypos,       1.0, 0.0 }
                };
                // Render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                // Update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, font._VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // Render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // Now advance cursors for next glyph
                x += (ch.Advance >> 6) * font.Size(); // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
            }
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}