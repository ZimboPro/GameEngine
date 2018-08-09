#include <graphics/Batch2dRenderer.hpp>

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
            glEnableVertexAttribArray(SHADER_COLOR_INDEX);
            
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, static_cast<const GLvoid *>(0));
            //glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, reinterpret_cast<const void *>(offsetof(VertexData, VertexData::color)));
            glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, reinterpret_cast<const void *>(offsetof(VertexData, uv)));
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

            int r = color.x * 255.0f;
            int g = color.y * 255.0f;
            int b = color.z * 255.0f;
            int a = color.w * 255.0f;

            uint32_t c = a << 24 | b << 16 | g << 8 | r;

            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon, 1.0f);
            this->_buffer->color = c;
            this->_buffer->uv = uv[0];
            this->_buffer++;

            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon.x, positon.y + size.y, positon.z, 1.0f);
            this->_buffer->color = c;
            this->_buffer->uv = uv[1];
            this->_buffer++;

            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon.x + size.x, positon.y + size.y, positon.z, 1.0f);
            this->_buffer->uv = uv[2];
            this->_buffer->color = c;
            this->_buffer++;

            this->_buffer->vertex = *(this->_transformationBack) * glm::vec4(positon.x + size.x, positon.y, positon.z, 1.0f);
            this->_buffer->uv = uv[3];
            this->_buffer->color = c;
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
            glBindVertexArray(this->_vao);
            this->_ibo->bind();

            glDrawElements(GL_TRIANGLES, this->_count, GL_UNSIGNED_SHORT, NULL);

            this->_ibo->unbind();
            glBindVertexArray(0);

            this->_count = 0;
        }
    }
}