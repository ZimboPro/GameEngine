#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Renderable2d::Renderable2d()
        {
            setUVDefaults();
            this->_texture = nullptr;
        }

        Renderable2d::Renderable2d(glm::vec2 size, glm::vec3 position, uint32_t color)
        {
            this->_position = position;
            this->_size = size;
            this->_color = color;
            this->_texture = nullptr;
            setUVDefaults();
        }
        
        Renderable2d::~Renderable2d()
        {}

          const glm::vec3 Renderable2d::Position() const
        {
            return (this->_position);
        }

         const glm::vec2 Renderable2d::getSize() const
        {
            return (this->_size);
        }

         const uint32_t Renderable2d::Color() const
        {
            return (this->_color);
        }

         void Renderable2d::submit(Renderer2d * renderer) const
        {
            const Renderable2d * render = this;
            renderer->submit(render);
        }

         const std::vector<glm::vec2> & Renderable2d::UV() const
        {
            return (this->_UV);
        }

         const GLuint Renderable2d::TextureID() const
        {
            return (this->_texture == nullptr) ? 0 : this->_texture->ID();
        }

        void Renderable2d::setUVDefaults()
        {
            this->_UV.push_back(glm::vec2(0,0));
            this->_UV.push_back(glm::vec2(0,1));
            this->_UV.push_back(glm::vec2(1,1));
            this->_UV.push_back(glm::vec2(1,0));
        }

         void Renderable2d::setColor(uint32_t color)
        {
            this->_color = color;
        }

        void Renderable2d::setColor(glm::vec4 color)
        {
            int r = color.x * 255.0f;
            int g = color.y * 255.0f;
            int b = color.z * 255.0f;
            int a = color.w * 255.0f;

            this->_color = a << 24 | b << 16 | g << 8 | r;
        }
    }
}