#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class Renderer2d
        {
            public:
                virtual ~Renderer2d() {};
                virtual void submit(const Renderable2d * renderable) = 0;
                virtual void flush() = 0; 
        };
    }
}
#endif