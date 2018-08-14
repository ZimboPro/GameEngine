#ifndef LABEL_HPP
#define LABEL_HPP

#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class Label : public Renderable2d
        {
            public:
                Label(std::string text, float x, float y, glm::vec4 color);
                virtual ~Label();
                virtual void submit(Renderer2d * renderer) const;

            private:
                std::string _text;
        };
    }
}

#endif