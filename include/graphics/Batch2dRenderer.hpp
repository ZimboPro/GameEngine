#ifndef BATCH2DRENDERER_HPP
# define BATCH2DRENDERER_HPP

#include <cstddef>
#include <graphics/Renderer2d.hpp>
#include <graphics/Renderable2d.hpp>
#include <graphics/buffers/IndexBuffer.hpp>

#define RENDER_MAX_SPRITES 10000
#define RENDER_VERTEX_SIZE sizeof(VertexData)
#define RENDER_SPRITE_SIZE RENDER_VERTEX_SIZE * 4
#define RENDER_BUFFER_SIZE RENDER_SPRITE_SIZE * RENDER_MAX_SPRITES
#define RENDER_INDICES_SIZE RENDER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

namespace GameEngine
{
    namespace graphics
    {
        class Batch2dRenderer : public Renderer2d
        {
            public:
                Batch2dRenderer();
                virtual ~Batch2dRenderer();
                virtual void submit(const Renderable2d * renderable) ;
                virtual void flush();
                virtual void begin();
                virtual void end();

            private:
                GLuint _vao;
                IndexBuffer * _ibo;
                GLsizei _count; 
                GLuint _vbo;
                VertexData * _buffer;
                std::vector<GLuint> _textureSlots;

                void Init();
        };
    }
}

#endif