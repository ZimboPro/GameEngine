#ifndef LABEL_HPP
#define LABEL_HPP

#include <graphics/Renderable2d.hpp>
#include <string>

namespace GameEngine
{
    namespace graphics
    {
        class Font;

        class Label : public Renderable2d
        {
            public:
                Label(std::string text, float x, float y, Font * font, uint32_t color);
                Label(std::string text, float x, float y, const std::string & font, uint32_t color);
                Label(std::string text, float x, float y, const std::string & font, unsigned int size, uint32_t color);
                virtual ~Label();
                virtual void submit(Renderer2d * renderer) ;

            private:
                std::string _text;
                Font * _font;
                void ValidateFont(const std::string & name) const;
                void ValidateFont(const std::string & name, unsigned int size) const;
        };
    }
}

#endif