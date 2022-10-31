#include <iostream>
#include <sstream>
#include <fstream>
#include "RenderSystem.h"

namespace ToyEngine {
    const std::string VERTEX_SHADER_PATH = "Shaders/ShaderX.glsl";
    const std::string FRAGMENT_SHADER_PATH = "Shaders/FragmentShader.glsl";


    void RenderSystem::tick()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(mShaderProgram);
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(mWindow.get());
        glfwPollEvents();
    }

    void RenderSystem::init(WindowPtr window) {
        mWindow = window;

        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mGeneratedBuffer);
        glGenBuffers(1, &mEBO);

        glBindVertexArray(mVAO);

        glBindBuffer(GL_ARRAY_BUFFER, mGeneratedBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        initShader();
    }

    void RenderSystem::initShader() {

        std::ifstream vertexInput(VERTEX_SHADER_PATH);
        std::ifstream fragmentInput(FRAGMENT_SHADER_PATH);
        if (!vertexInput || !fragmentInput) {
            std::cout << "ERROR::IO: either vertex shader or fragment shader cannot be read from the path";
        }

        std::stringstream vertexStringStream;
        std::stringstream fragmentStringStream;
        vertexStringStream << vertexInput.rdbuf();
        fragmentStringStream << fragmentInput.rdbuf();

        vertexInput.close();
        fragmentInput.close();

        std::string vertexString = vertexStringStream.str();
        std::string fragmentString = fragmentStringStream.str();

        const char* cstr_vertex = vertexString.c_str();
        const char* cstr_fragment = fragmentString.c_str();

        GLuint vertexShader;
        GLuint fragmentShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


        glShaderSource(vertexShader, 1, &cstr_vertex, NULL);
        glShaderSource(fragmentShader, 1, &cstr_fragment, NULL);
        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        GLint success;
        char log[500];
        glGetShaderiv(vertexShader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(vertexShader, sizeof(log), NULL, log);
            std::cout << "ERROR::SHADER::LINKING_FAILED\n" << log << std::endl;
        }
        glGetShaderiv(fragmentShader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(fragmentShader, sizeof(log), NULL, log);
            std::cout << "ERROR::SHADER::LINKING_FAILED\n" << log << std::endl;
        }

        mShaderProgram = glCreateProgram();
        glAttachShader(mShaderProgram, vertexShader);
        glAttachShader(mShaderProgram, fragmentShader);
        glLinkProgram(mShaderProgram);

        glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(mShaderProgram, 512, NULL, log);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
        }


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

}
