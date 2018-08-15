#include <graphics/Sprite.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Sprite::Sprite(float x, float y, float width, float height, uint32_t  color) :
                 Renderable2d(glm::vec2(width, height) ,glm::vec3(x, y, 0),  color)
        {
            
        }

        Sprite::Sprite(float x, float y, float width, float height, Texture * texture) :
                 Renderable2d(glm::vec2(width, height) ,glm::vec3(x, y, 0),  0xffffffff)
        {
            this->_texture = texture;
        }

        Sprite::~Sprite()
        {
            
        }
    }
}