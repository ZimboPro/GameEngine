#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <Maths.hpp>
#include <vector>


namespace GameEngine
{
    namespace graphics
    {
        class Renderable2d;
        
        class Renderer2d
        {
            public:
                Renderer2d();
                virtual ~Renderer2d();
                virtual void begin() = 0;
                virtual void end() = 0;
                virtual void submit(const Renderable2d * renderable) = 0;
                virtual void flush() = 0;
                void push(glm::mat4 matrix, bool OverRide = false);
                void pop();

            protected:
                glm::mat4 *_transformationBack;
                std::vector<glm::mat4> _transformationStack;
        };
    }
}
#endif