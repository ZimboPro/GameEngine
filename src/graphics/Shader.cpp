#include <graphics/Shader.hpp>
#include <utils/FileUtils.hpp>
#include <Maths.hpp>
#include <iostream>

namespace GameEngine
{
    namespace graphics
    {
        Shader::Shader(const char *vertPath, const char *fragPath) : _vertPath(vertPath), _fragPath(fragPath)
        {
            this->_shader = Load(); 
        }

        Shader::~Shader()
        { 
            glDeleteProgram(this->_shader); 
        }

        void Shader::enable()
        {
            glUseProgram(this->_shader);
        }

        void Shader::disable()
        {
            glUseProgram(0); 
        }

        GLuint CompileShaders(GLenum shaderType, const char * path)
        {
            GLuint shader = glCreateShader(shaderType);

            std::string s = readFile(path);
            const char * source = s.c_str();
            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);

            GLint result;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
            char info[512];
            if (result == GL_FALSE)
            {
                std::string error = (shaderType == GL_VERTEX_SHADER) ? "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" : "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
                glGetShaderInfoLog(shader, 512, NULL, info);
                std::cout << error << info << std::endl;
                glDeleteShader(shader);
                return (0);
            }
            return shader;
        }

        GLuint Shader::Load()
        {
            GLuint program = glCreateProgram();
            GLuint vertex = CompileShaders(GL_VERTEX_SHADER, this->_vertPath);
            if (!vertex)
                return (0);

            GLuint fragment = CompileShaders(GL_FRAGMENT_SHADER, this->_fragPath);
            if (!fragment)
                return (0); 
            
            glAttachShader(program, vertex);
            glAttachShader(program, fragment);

            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(vertex);
            glDeleteShader(fragment); 

            return program;
        }

        inline GLuint Shader::Value() const
        {
            return (this->_shader);
        }

        GLint Shader::UniformLocation(const GLchar * name)
        {
            return glGetUniformLocation(this->_shader, name);
        }

        GLint Shader::UniformLocation(const GLchar * name) const
        {
            return glGetUniformLocation(this->_shader, name);
        }

        void Shader::setUniform1f(const GLchar * name, float value)
        {
            glUniform1f(UniformLocation(name), value);
        }

        void Shader::setUniform1i(const GLchar * name, int value)
        {
            glUniform1i(UniformLocation(name), value);
        }

        void Shader::setUniform1fv(const GLchar * name, int count, float* value)
        {
            glUniform1fv(UniformLocation(name), count, value);
        }

        void Shader::setUniform1iv(const GLchar * name, int count, int* value)
        {
            glUniform1iv(UniformLocation(name), count, value);
        }

        void Shader::setUniform2f(const GLchar * name, glm::vec2 value)
        {
            glUniform2f(UniformLocation(name), value.x, value.y);
        }

        void Shader::setUniform3f(const GLchar * name, glm::vec3 value)
        {
            glUniform3f(UniformLocation(name), value.x, value.y, value.z);
        }

        void Shader::setUniform4f(const GLchar * name, glm::vec4 value)
        {
            glUniform4f(UniformLocation(name), value.x, value.y, value.z, value.w);
        }

        void Shader::setUniformMat4f(const GLchar * name, glm::mat4 value)
        { 
            const GLfloat * temp = glm::value_ptr<glm::mat4>(value); 
            glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, temp);
        }

         void Shader::setUniform1f(const GLchar * name, float value) const
        {
            glUniform1f(UniformLocation(name), value);
        }

        void Shader::setUniform1i(const GLchar * name, int value) const
        {
            glUniform1i(UniformLocation(name), value);
        }

        void Shader::setUniform2f(const GLchar * name, glm::vec2 value) const
        {
            glUniform2f(UniformLocation(name), value.x, value.y);
        }

        void Shader::setUniform3f(const GLchar * name, glm::vec3 value) const
        {
            glUniform3f(UniformLocation(name), value.x, value.y, value.z);
        }

        void Shader::setUniform4f(const GLchar * name, glm::vec4 value) const
        {
            glUniform4f(UniformLocation(name), value.x, value.y, value.z, value.w);
        }

        void Shader::setUniformMat4f(const GLchar * name, glm::mat4 value) const
        { 
            const GLfloat * temp = glm::value_ptr<glm::mat4>(value); 
            glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, temp);
        }
    }
}