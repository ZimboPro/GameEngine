#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameEngine
{
    namespace graphics
    {
        class Window
        {
            public:
                Window(const char * title, unsigned int w, unsigned int h);
                ~Window();
                void update();
                bool closed() const;
                void clear() const;
                void clear(int8_t & r, int8_t g, int8_t b) const;

                unsigned int Width() const;
                unsigned int Height() const;

                bool hasResized();
                
            private:
                const char * _title;
                unsigned int _width;
                unsigned int _height;
                GLFWwindow * _win;

                bool Init();

        };
    }
}

#endif