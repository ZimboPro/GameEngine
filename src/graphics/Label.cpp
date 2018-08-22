#include <graphics/Label.hpp>
#include <graphics/Renderer2d.hpp>
#include <graphics/Font.hpp>
#include <graphics/FontManager.hpp>
#include <iostream>

namespace GameEngine
{
    namespace graphics
    {
        Label::Label(std::string text, float x, float y, Font * font, uint32_t color) : Renderable2d()
        {
            this->_text = text;
            this->_texture = nullptr;
            this->_color = color;
            this->_position = glm::vec3(x, y, 0.0f);
            this->_font = font;
        }

        Label::Label(std::string text, float x, float y, const std::string & font, uint32_t color)
        {
            this->_text = text;
            this->_texture = nullptr;
            this->_color = color;
            this->_position = glm::vec3(x, y, 0.0f);
            this->_font = FontManager::get(font);
        }

        Label::Label(std::string text, float x, float y, const std::string & font, unsigned int size, uint32_t color)
        {
            this->_text = text;
            this->_texture = nullptr;
            this->_color = color;
            this->_position = glm::vec3(x, y, 0.0f);
            this->_font = FontManager::get(font, size);
        }

        Label::~Label()
        {}

        void Label::submit(Renderer2d * renderer) 
        {
            renderer->drawString(this->_text, this->_position, *this->_font, this->_color);
        }

        void Label::ValidateFont(const std::string & name) const
        {
            if (this->_font == nullptr)
                std::cout << "Font " << name << " doesn't exist in Font Manager" << std::endl;
        }

        void Label::ValidateFont(const std::string & name, unsigned int size) const
        {
            if (this->_font == nullptr)
                std::cout << "Font " << name << " and size " << size << " doesn't exist in Font Manager" << std::endl;
        }
    }
}
