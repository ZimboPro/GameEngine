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
                bool closed() ;
                void clear() ;
                void clear(int8_t & r, int8_t g, int8_t b) ;

                unsigned int Width() ;
                unsigned int Height() ;

                bool isKeyPressed(int keycode) ;
                bool isKeyTyped(int keycode) ;
                bool isButtonPressed(int button) ;
                bool isButtonClicked(int button) ;
                void CursorPostion(double &x, double & y) ;
 
            private:
                const char * _title;
                unsigned int _width;
                unsigned int _height;
                GLFWwindow * _win;

                bool _keys[MAX_KEYS];
                bool _keyState[MAX_KEYS];
                bool _keyTyped[MAX_KEYS];
                bool _buttons[MAX_BUTTONS];
                bool _buttonState[MAX_BUTTONS];
                bool _buttonClicked[MAX_BUTTONS];
                double _mouseX;
                double _mouseY;

                friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
                friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
                friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
                friend void window_resize(GLFWwindow * window, int width, int height);

                bool Init();
        };
    }
}

#endif