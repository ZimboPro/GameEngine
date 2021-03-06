#ifndef SHADER_HPP
#define SHADER_HPP

#include <Maths.hpp>
#include <glad/glad.h>
#include <iostream>

namespace GameEngine
{
    namespace graphics
    {
        class Shader
        {
            public:
                Shader(const std::string & vertexpath, const std::string & fragpath);
                ~Shader();

                void enable();
                void disable();
                unsigned int ID() const;
                
                void setBool(const std::string &name, bool value) const;  
                void setInt(const std::string &name, int value) const;   
                void setFloat(const std::string &name, float value) const;

                void setVec2(const std::string &name, const glm::vec2 &value) const;
                void setVec2(const std::string &name, float x, float y) const;
                void setVec3(const std::string &name, const glm::vec3 &value) const;
                void setVec3(const std::string &name, float x, float y, float z) const;
                void setVec4(const std::string &name, const glm::vec4 &value) const;
                void setVec4(const std::string &name, float x, float y, float z, float w) const;

                void setMat2(const std::string &name, const glm::mat2 &mat) const;
                void setMat3(const std::string &name, const glm::mat3 &mat) const;
                void setMat4(const std::string &name, const glm::mat4 &mat) const;
                void setMat4Complete(const std::string &name, const glm::mat4 &mat) const;
            
            private:
                void CreateShaderProgam(int vs, int fs);
                unsigned int CompileShader(unsigned int type, const char * src);
                std::string const GetSource(const std::string & path);

                unsigned int _ID;
        };
    }
}

#endif