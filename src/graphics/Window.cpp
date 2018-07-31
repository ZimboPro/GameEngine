#include "Window.hpp"
#include <iostream>

namespace GameEngine
{
    namespace graphics
    {
        Window::Window(const char *title, unsigned int w, unsigned int h) : _title(title)
        {
            this->_height = h;
            this->_width = w;
            if (!Init())
                glfwTerminate();
        }

        Window::~Window()
        {
            glfwTerminate();
        }

        void Window::update()
        {
            glfwSwapBuffers(this->_win);
            
            glfwPollEvents();
        }

        bool failed(char const * str)
        {
            std::cout << str << std::endl;
            return false;
        }

        bool Window::Init()
        {
            if (!glfwInit())
            {
                return failed("GameEngine failed to initialise");
            }
            this->_win = glfwCreateWindow(this->_width, this->_height,this->_title, NULL, NULL);
            if (!this->_win)
            {
                return failed("Failed to create window");
            }
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                return failed("Failed to initialize GLAD");
            } 
            glfwMakeContextCurrent(this->_win);
            return true;
        }

        bool Window::closed() const
        {
            return glfwWindowShouldClose(this->_win) == 1;
        }

        void Window::clear() const
        {
            int8_t r = 0;
            Window::clear(r, r, r);
        }

        void Window::clear(int8_t & r, int8_t g, int8_t b) const
        {
            float red = static_cast<float>(r) / 255.0f;
            float green = static_cast<float>(g) / 255.0f;
            float blue = static_cast<float>(b) / 255.0f;
            glClearColor(red, green, blue, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        inline unsigned int Window::Width() const
        {
            return this->_width;
        }

        inline unsigned int Window::Height() const
        {
            return this->_height;
        }

        bool Window::hasResized()
        {
            int h;
            int w;
            glfwGetFramebufferSize(this->_win, &w, &h);
            if (this->_width != w && this->_height != h)
            {
                this->_width = w;
                this->_height = h;
                glViewport(0, 0, this->_width, this->_height);
                return true;
            }
            return false;
        }
    } // namespace graphics
} // namespace GameEngine