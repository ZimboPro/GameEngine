#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <Maths.hpp>
#include <vector>
//#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class Renderable2d;
        class Font;
        
        class Renderer2d
        {
            public:
                Renderer2d();
                virtual ~Renderer2d();
                virtual void begin() = 0;
                virtual void end() = 0;
                virtual void submit(Renderable2d * renderable) = 0;
                virtual void flush() = 0;
                void push(glm::mat4 matrix, bool OverRide = false);
                void pop();
                virtual void drawString(const std::string & text, const glm::vec3 & position, const Font & font, const uint32_t & color) = 0;

            protected:
                glm::mat4 *_transformationBack;
                std::vector<glm::mat4> _transformationStack;
        };
    }
}
#endif