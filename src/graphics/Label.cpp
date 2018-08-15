#include <graphics/Label.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Label::Label(std::string text, float x, float y, uint32_t color) : Renderable2d()
        {
            this->_text = text;
            this->_texture = nullptr;
            this->_color = color;
            this->_position = glm::vec3(x, y, 0.0f);
        }

        Label::~Label()
        {}

        void Label::submit(Renderer2d * renderer) const
        {
            renderer->drawString(this->_text, this->_position, this->_color);
        }
    }
}
