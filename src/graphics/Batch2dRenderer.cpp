#include <graphics/Batch2dRenderer.hpp>
#include <freetype-gl.h>

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
            
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, static_cast<const GLvoid *>(0));
            glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, reinterpret_cast<const void *>(offsetof(VertexData, uv)));
            glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, reinterpret_cast<const void *>(offsetof(VertexData, tid)));
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDER_VERTEX_SIZE, reinterpret_cast<const void *>(offsetof(VertexData, color)));
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
            //depth set to one channel
            // this->_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
            this->_FTAtlas = ftgl::texture_atlas_new(512, 512, 3);
            this->_FTFont = ftgl::texture_font_new_from_file(this->_FTAtlas, 20, "arial.ttf");
        }

        void Batch2dRenderer::begin()
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
            this->_buffer =  reinterpret_cast<VertexData *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        }

        void Batch2dRenderer::submit(const Renderable2d * renderable)
        {
            const glm::vec3 positon = renderable->Position();
            const glm::vec2 size = renderable->getSize();
            const glm::vec4 color = renderable->Color();
            const std::vector<glm::vec2>& uv = renderable->UV();
            const GLuint tid = renderable->TextureID();

            float ts = 0.0f;
            uint32_t c = 0;
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
            // else
            // {
                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.w * 255.0f;

                c = a << 24 | b << 16 | g << 8 | r;
            // }


            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon, 1.0f);
            this->_buffer->color = c;
            this->_buffer->uv = uv[0];
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon.x, positon.y + size.y, positon.z, 1.0f);
            this->_buffer->color = c;
            this->_buffer->uv = uv[1];
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon.x + size.x, positon.y + size.y, positon.z, 1.0f);
            this->_buffer->uv = uv[2];
            this->_buffer->color = c;
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon.x + size.x, positon.y, positon.z, 1.0f);
            this->_buffer->uv = uv[3];
            this->_buffer->color = c;
            this->_buffer->tid = ts;
            this->_buffer++;

            this->_count += 6;
        }

        void Batch2dRenderer::end()
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
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

        void Batch2dRenderer::drawString(const std::string & text, const glm::vec3 & position, const glm::vec4 & color)
        {
            float ts = 0.0f;
            uint32_t col = 0;

            int r = color.x * 255.0f;
            int g = color.y * 255.0f;
            int b = color.z * 255.0f;
            int a = color.w * 255.0f;

            col = a << 24 | b << 16 | g << 8 | r;

            bool found = false;
            for (size_t i = 0; i < this->_textureSlots.size(); i++)
            {
                if (this->_textureSlots[i] == this->_FTAtlas->id)
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
                this->_textureSlots.push_back(this->_FTAtlas->id);
                ts = static_cast<float>(this->_textureSlots.size());
            }

            float scaleX = 960.0f / 32.0f;
            float scaleY = 540.0f / 18.0f;

            float x = position.x;

            for (size_t i = 0; i < text.length(); i++)
            {
                char c = text[i];
                texture_glyph_t * glyph = ftgl::texture_font_get_glyph(this->_FTFont, &c);
                if (glyph != NULL)
                {
                    if (i > 0)
                    {
                        float kerning = ftgl::texture_glyph_get_kerning(glyph, &text[i - 1]);
                        x += kerning / scaleX;
                    }

                    float x0 = x + glyph->offset_x / scaleX;
                    float y0 = position.y + glyph->offset_y / scaleY;
                    float x1 = x0 + glyph->width / scaleX;
                    float y1 = y0 - glyph->height / scaleY;

                    float u0 = glyph->s0;
                    float v0 = glyph->t0;
                    float u1 = glyph->s1;
                    float v1 = glyph->t1;

                    this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(x0, y0, 0, 1.0f);
                    this->_buffer->uv = glm::vec2(u0, v0);
                    this->_buffer->tid = ts;
                    this->_buffer->color = col;
                    this->_buffer++;

                    this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(x0, y1, 0, 1.0f);
                    this->_buffer->uv = glm::vec2(u0, v1);
                    this->_buffer->tid = ts;
                    this->_buffer->color = col;
                    this->_buffer++;

                    this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(x1, y1, 0, 1.0f);
                    this->_buffer->uv = glm::vec2(u1, v1);
                    this->_buffer->tid = ts;
                    this->_buffer->color = col;
                    this->_buffer++;

                    this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(x1, y0, 0, 1.0f);
                    this->_buffer->uv = glm::vec2(u1, v0);
                    this->_buffer->tid = ts;
                    this->_buffer->color = col;
                    this->_buffer++;
            
                    this->_count += 6;
                    x += glyph->advance_x /scaleX;
                }
            }
        }
    }
}