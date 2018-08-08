#ifndef GROUP_HPP
#define GROUP_HPP

#include <graphics/Renderable2d.hpp>
#include <vector>
#include <Maths.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class Group : public Renderable2d
        {
            public:
                Group(const glm::mat4 & tranform);
                ~Group();
                virtual void submit(Renderer2d * renderer) const;

                void add(Renderable2d * renderable);

            private:
                std::vector<Renderable2d *> _renderables;
                glm::mat4 _transformationMatrix;
        };
    }
}
#endif