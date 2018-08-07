#ifndef TILELAYER_HPP
#define TILELAYER_HPP

#include <graphics/layers/Layer.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class TileLayer : public Layer
        {
            public:
                TileLayer(Shader *shader);
                virtual ~TileLayer();

            protected:
                
        };
    }
}
#endif