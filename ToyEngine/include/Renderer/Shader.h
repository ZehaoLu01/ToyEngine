#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace ToyEngine {
    class Shader
    {
    public:
        unsigned int ID;
        // constructor generates the shader on the fly
        Shader(const char* vertexPath, const char* fragmentPath);

        // activate the shader
        void use()
        {
            glUseProgram(ID);
        }

        // utility uniform functions
        void setUniform(const std::string& name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }

        void setUniform(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setUniform(const std::string& name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setUniform(const std::string& name, glm::mat4 value)const 
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
        }

    private:
        // utility function for checking shader compilation/linking errors.
        void checkCompileErrors(unsigned int shader, std::string type);
    };
}
