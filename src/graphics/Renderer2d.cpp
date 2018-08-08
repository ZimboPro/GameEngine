#include <graphics/Renderer2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        Renderer2d::Renderer2d()
        {
            this->_transformationStack.push_back(glm::mat4(1.0f));
            this->_transformationBack = &(this->_transformationStack.back());
        }

        Renderer2d::~Renderer2d()
        {}

        void Renderer2d::push(glm::mat4 matrix, bool OverRide)
        {
            if (!OverRide)
                this->_transformationStack.push_back(*(this->_transformationBack) * matrix);
            else
                this->_transformationStack.push_back(matrix);
            this->_transformationBack = &(this->_transformationStack.back());
        }

        void Renderer2d::pop()
        {
            if (this->_transformationStack.size() > 1)
                this->_transformationStack.pop_back();
            this->_transformationBack = &(this->_transformationStack.back());
        }
    }
}