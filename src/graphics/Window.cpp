#include <graphics/Window.hpp>
#include <iostream>

namespace GameEngine
{
    namespace graphics
    {
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
            win->_keys[key] = action != GLFW_RELEASE; 
        }
        
        void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
        {
            Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
            win->_mouseX = xpos;
            win->_mouseY = ypos;
        }

        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
        {
            Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
            win->_buttons[button] = action != GLFW_RELEASE;
        }
        

        Window::Window(const char *title, unsigned int w, unsigned int h) : _title(title)
        {
            this->_height = h;
            this->_width = w;
            if (!Init())
                glfwTerminate();
            
            for (int i = 0; i < MAX_KEYS; i++)
                this->_keys[i] = false;
            for (int i = 0; i < MAX_BUTTONS; i++)
                this->_buttons[i] = false;
        }

        Window::~Window()
        {
            glfwTerminate();
        }

        void Window::update()
        {
            GLenum error = glGetError();

            if (error != GL_NO_ERROR)
                std::cout << "OpenGL error: " << error << std::endl;

            glfwSwapBuffers(this->_win);
            glfwPollEvents();
        }

        bool failed(char const * str)
        {
            std::cout << str << std::endl;
            return false;
        }

        bool Window::isKeyPressed(int keycode) const
        {
            if (keycode >= MAX_KEYS)
                return false;
            return _keys[keycode];
        }

        bool Window::isButtonPressed(int button) const
        {
            if (button >= MAX_BUTTONS)
                return false;
            return _buttons[button];
        }

        void Window::CursorPostion(double &x, double & y) const
        {
            x = _mouseX;
            y = _mouseY;
        }

        bool Window::Init()
        {
            if (!glfwInit())
                return failed("GameEngine failed to initialise");
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            this->_win = glfwCreateWindow(this->_width, this->_height,this->_title, NULL, NULL);
            if (!this->_win)
                return failed("Failed to create window");
            glfwMakeContextCurrent(this->_win);

            glfwSetKeyCallback(this->_win, key_callback);
            glfwSetCursorPosCallback(this->_win, cursor_position_callback);
            glfwSetMouseButtonCallback(this->_win, mouse_button_callback);

            //doesn't cap fps
            glfwSwapInterval(0.0);

            glfwSetWindowUserPointer(this->_win, this);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                return failed("Failed to initialize GLAD");
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
            if (this->_width != static_cast<unsigned int>(w) &&
                    this->_height != static_cast<unsigned int>(h))
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
