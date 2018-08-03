#ifndef SIMPLERENDERER2D_HPP
#define SIMPLERENDERER2D_HPP

#include <glad/glad.h>
#include <Maths.hpp>
#include <graphics/Renderer2d.hpp>
#include <deque>

namespace GameEngine
{
    namespace graphics
    {
        class SimpleRenderer2d : public Renderer2d
        {
            public:
                virtual void submit(const Renderable2d * renderable);
                virtual void flush();
                virtual ~SimpleRenderer2d();
            private:
                std::deque<const Renderable2d *> _renderQueue;
        };
    }
}

#endif