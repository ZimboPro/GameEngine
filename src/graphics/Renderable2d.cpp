#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Renderable2d::Renderable2d()
        {
            setUVDefaults();
            this->_texture == nullptr;
        }

        Renderable2d::Renderable2d(glm::vec2 size, glm::vec3 position, glm::vec4 color)
        {
            this->_position = position;
            this->_size = size;
            this->_color = color;
            this->_texture == nullptr;
            setUVDefaults();
        }
        
        Renderable2d::~Renderable2d()
        {}

        inline  const glm::vec3 Renderable2d::Position() const
        {
            return (this->_position);
        }

        inline const glm::vec2 Renderable2d::getSize() const
        {
            return (this->_size);
        }

        inline const glm::vec4 Renderable2d::Color() const
        {
            return (this->_color);
        }

        inline void Renderable2d::submit(Renderer2d * renderer) const
        {
            const Renderable2d * render = this;
            renderer->submit(render);
        }

        inline const std::vector<glm::vec2> & Renderable2d::UV() const
        {
            return (this->_UV);
        }

        inline const GLuint Renderable2d::TextureID() const
        {
            if (this->_texture == nullptr)
                return 0;
            return this->_texture->ID();
        }

        void Renderable2d::setUVDefaults()
        {
            this->_UV.push_back(glm::vec2(0,0));
            this->_UV.push_back(glm::vec2(0,1));
            this->_UV.push_back(glm::vec2(1,1));
            this->_UV.push_back(glm::vec2(1,0));
        }
    }
}