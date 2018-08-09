#include <graphics/Sprite.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Sprite::Sprite(float x, float y, float width, float height, glm::vec4  color) :
                 Renderable2d(glm::vec2(width, height) ,glm::vec3(x, y, 0),  color)
        {
            
        }

        Sprite::Sprite(float x, float y, float width, float height, Texture * texture) :
                 Renderable2d(glm::vec2(width, height) ,glm::vec3(x, y, 0),  glm::vec4(1.0f))
        {
            this->_texture = texture;
        }

        Sprite::~Sprite()
        {
            
        }
    }
}