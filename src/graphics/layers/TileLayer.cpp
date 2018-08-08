#include <graphics/layers/TileLayer.hpp>
#include <graphics/Batch2dRenderer.hpp>
#include <graphics/Window.hpp>
#include <Maths.hpp>

namespace GameEngine
{
    namespace graphics
    {
        TileLayer::TileLayer(Shader *shader) : Layer(new Batch2dRenderer(), shader, glm::ortho(-16.0f, 16.0f, -9.0f, 7.0f, 0.1f, 100.0f))
        {
        }

        TileLayer::~TileLayer()
        {
        }
    }
}
