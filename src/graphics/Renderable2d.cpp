#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Renderable2d::Renderable2d()
        {}

        Renderable2d::Renderable2d(glm::vec2 size, glm::vec3 position, glm::vec4 color)
        {
            this->_position = position;
            this->_size = size;
            this->_color = color;  
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
    }
}