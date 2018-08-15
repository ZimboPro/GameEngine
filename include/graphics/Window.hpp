#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameEngine
{
    namespace graphics
    {
        #define MAX_KEYS 1024
        #define MAX_BUTTONS 32 

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

                bool isKeyPressed(int keycode) const;
                bool isKeyTyped(int keycode) const;
                bool isButtonPressed(int button) const;
                bool isButtonClicked(int button) const;
                void CursorPostion(double &x, double & y) const;
 
            private:
                const char * _title;
                unsigned int _width;
                unsigned int _height;
                GLFWwindow * _win;

                static bool _keys[MAX_KEYS];
                static bool _keyState[MAX_KEYS];
                static bool _keyTyped[MAX_KEYS];
                static bool _buttons[MAX_BUTTONS];
                static bool _buttonState[MAX_BUTTONS];
                static bool _buttonClicked[MAX_BUTTONS];
                static double _mouseX;
                static double _mouseY;

                friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
                friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
                friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
                friend void window_resize(GLFWwindow * window, int width, int height);

                bool Init();
        };
    }
}

#endif