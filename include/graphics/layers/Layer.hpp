#ifndef LAYER_HPP
#define LAYER_HPP

#include <graphics/Renderable2d.hpp>
#include <vector>

namespace GameEngine
{
    namespace graphics
    {
        class Layer
        {
            public:
                Layer();
                virtual ~Layer();
                virtual void add(Renderable2d * renderable);
                virtual void render();

                 std::vector<Renderable2d *> & Renderables() ;

            protected:
                Layer(Renderer2d * renderer, Shader *shader, glm::mat4 projMatrix);
                Renderer2d * _renderer;
                std::vector<Renderable2d *> _renderables;
                Shader * _shader;
                glm::mat4 _projectionMatrix;
        };
    }
}

#endif