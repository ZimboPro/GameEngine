#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <graphics/Renderable2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class Sprite : public Renderable2d
        {
            public:
                Sprite(float x, float y, float width, float height, glm::vec4  color);
                Sprite(float x, float y, float width, float height, Texture *texture);
                ~Sprite();
        };
    }
}

#endif