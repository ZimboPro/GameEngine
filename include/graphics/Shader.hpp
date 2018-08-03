#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace GameEngine
{
    namespace graphics
    {
        class Shader
        {
            public:
                Shader(const char * vertPath, const char * fragPath);
                ~Shader();

                void enable();
                void disable();
                GLuint Value() const;

                void setUniform1f(const GLchar * name, float value);
                void setUniform1i(const GLchar * name, int value);
                void setUniform2f(const GLchar * name, glm::vec2 value);
                void setUniform3f(const GLchar * name, glm::vec3 value);
                void setUniform4f(const GLchar * name, glm::vec4 value);
                void setUniformMat4f(const GLchar * name, glm::mat4 value);

                void setUniform1f(const GLchar * name, float value) const;
                void setUniform1i(const GLchar * name, int value) const;
                void setUniform2f(const GLchar * name, glm::vec2 value) const;
                void setUniform3f(const GLchar * name, glm::vec3 value) const;
                void setUniform4f(const GLchar * name, glm::vec4 value) const;
                void setUniformMat4f(const GLchar * name, glm::mat4 value) const;

            private:
                GLint UniformLocation(const GLchar * name);
                GLint UniformLocation(const GLchar * name) const;
                GLuint _shader;
                const char * _vertPath;
                const char * _fragPath;
                GLuint Load();
        };
    }
}

#endif