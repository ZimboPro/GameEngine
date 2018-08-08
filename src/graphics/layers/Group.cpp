#include <graphics/layers/Group.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Group::Group(const glm::mat4 & tranform)
        {
            this->_transformationMatrix = tranform;
        }

        Group::~Group()
        {
            for (size_t i = 0; i < this->_renderables.size(); i++)
                delete this->_renderables[i];
            this->_renderables.clear();
        }

        void Group::add(Renderable2d * renderable)
        {
            this->_renderables.push_back(renderable);
        }

        void Group::submit(Renderer2d * renderer) const
        {
            renderer->push(this->_transformationMatrix);
            for (const Renderable2d * renderable : this->_renderables)
                renderable->submit(renderer);
            renderer->pop();
        }

    }
}