#include <graphics/Window.hpp>
#include <graphics/FontManager.hpp>
#include <iostream>
#include <cstring>

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

        void window_resize(GLFWwindow * window, int width, int height)
        {
            glViewport(0, 0, width, height);
            Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
            win->_height = height;
            win->_width = width;
        }
        

        Window::Window(const char *title, unsigned int w, unsigned int h) : _title(title)
        {
            this->_height = h;
            this->_width = w;
            if (!Init())
                glfwTerminate();
            
            for (int i = 0; i < MAX_KEYS; i++)
            {
                this->_keys[i] = false;
                this->_keyState[i] = false;
                this->_keyTyped[i] = false;
            }
            for (int i = 0; i < MAX_BUTTONS; i++)
            {
                this->_buttons[i] = false;
                this->_buttonState[i] = false;
                this->_buttonClicked[i] = false;
            }
        }

        Window::~Window()
        {
            FontManager::clean();
            glfwTerminate();
        }

        void Window::update()
        {
            for (int i = 0; i < MAX_KEYS; i++)
                this->_keyTyped[i] = this->_keys[i] && !this->_keyState[i];
            memcpy(this->_keyState, this->_keys, MAX_KEYS);

            for (int i = 0; i < MAX_BUTTONS; i++)
                this->_buttonClicked[i] = this->_buttons[i] && !this->_buttonState[i];
            memcpy(this->_buttonState, this->_buttons, MAX_BUTTONS);


            GLenum error = glGetError();

            if (error != GL_NO_ERROR)
                std::cout << "OpenGL error: " << error << std::endl;

            glfwSwapBuffers(this->_win);
            glfwPollEvents();
        }

        bool failed(char  * str)
        {
            std::cout << str << std::endl;
            return false;
        }

        bool Window::isKeyPressed(int keycode) 
        {
            if (keycode >= MAX_KEYS)
                return false;
            return _keys[keycode];
        }

        bool Window::isKeyTyped(int keycode) 
        {
            if (keycode >= MAX_KEYS)
                return false;
            return _keyTyped[keycode];
        }

        bool Window::isButtonPressed(int button) 
        {
            if (button >= MAX_BUTTONS)
                return false;
            return _buttons[button];
        }

        bool Window::isButtonClicked(int button) 
        {
            if (button >= MAX_BUTTONS)
                return false;
            return this->_buttonClicked [button];
        }

        void Window::CursorPostion(double &x, double & y) 
        {
            x = _mouseX;
            y = _mouseY;
        }

        bool Window::Init()
        {
            if (!glfwInit())
                return failed("GameEngine failed to initialise");
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            this->_win = glfwCreateWindow(this->_width, this->_height,this->_title, NULL, NULL);
            if (!this->_win)
                return failed("Failed to create window");
            glfwMakeContextCurrent(this->_win);

            glfwSetKeyCallback(this->_win, key_callback);
            glfwSetCursorPosCallback(this->_win, cursor_position_callback);
            glfwSetMouseButtonCallback(this->_win, mouse_button_callback);
            glfwSetFramebufferSizeCallback(this->_win, window_resize);

            //doesn't cap fps
            glfwSwapInterval(0.0);

            glfwSetWindowUserPointer(this->_win, this);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                return failed("Failed to initialize GLAD");
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            return true;
        }

        bool Window::closed() 
        {
            return glfwWindowShouldClose(this->_win) == 1;
        }

        void Window::clear() 
        {
            int8_t r = 0;
            Window::clear(r, r, r);
        }

        void Window::clear(int8_t & r, int8_t g, int8_t b) 
        {
            float red = static_cast<float>(r) / 255.0f;
            float green = static_cast<float>(g) / 255.0f;
            float blue = static_cast<float>(b) / 255.0f;
            glClearColor(red, green, blue, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        unsigned int Window::Width() 
        {
            return this->_width;
        }

        unsigned int Window::Height() 
        {
            return this->_height;
        }
    }
}
