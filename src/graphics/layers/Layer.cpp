#include <graphics/layers/Layer.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Layer::Layer()
        {
            this->_shader->enable();
            this->_shader->setUniformMat4f("pr_matrix", this->_projectionMatrix);
            this->_shader->disable();
        }

        Layer::Layer(Renderer2d * renderer, Shader *shader, glm::mat4 projMatrix) : _renderer(renderer)
        {
            this->_projectionMatrix = projMatrix;
            this->_shader = shader;

            this->_shader->enable();
            this->_shader->setUniformMat4f("pr_matrix", this->_projectionMatrix);
            this->_shader->disable();
        }

        Layer::~Layer()
        {
            delete this->_shader;
            delete this->_renderer;
            for(size_t i = 0; i < this->_renderables.size(); i++)
                delete this->_renderables[i];
        }

        void Layer::add(Renderable2d * renderable)
        {
            this->_renderables.push_back(renderable);
        }

        void Layer::render()
        {
            this->_shader->enable();

            this->_renderer->begin();
            for (Renderable2d * renderable : this->_renderables)
            {
                this->_renderer->submit(renderable);
            }
            this->_renderer->end();

            this->_renderer->flush();
        }
    }
}