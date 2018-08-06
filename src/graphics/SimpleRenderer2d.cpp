#include <graphics/SimpleRenderer2d.hpp>

namespace GameEngine
{
    namespace graphics
    {
        SimpleRenderer2d::~SimpleRenderer2d()
        {}

        void SimpleRenderer2d::submit(const Renderable2d * renderable)
        {
            this->_renderQueue.push_back(static_cast<const StaticSprite *>(renderable));
        }

        void SimpleRenderer2d::flush()
        {
            while (!this->_renderQueue.empty())
            {
                const StaticSprite * renderable = this->_renderQueue.front(); 
                renderable->getVAO()->bind();
                renderable->getIBO()->bind();

                //check if matrix is correct
                glm::vec4 temp(renderable->Position(), 0);
                glm::mat4 t(0.0f);
                t[3] = temp;
                renderable->getShader().setUniformMat4f("m_matrix", t);
                glDrawElements(GL_TRIANGLES, renderable->getIBO()->Count(), GL_UNSIGNED_SHORT, 0);

                renderable->getIBO()->unbind();
                renderable->getVAO()->unbind();

                this->_renderQueue.pop_front();
            }
        }
    }
}