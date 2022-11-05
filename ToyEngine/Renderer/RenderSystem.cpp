#include <iostream>
#include <sstream>
#include <fstream>
#include "RenderSystem.h"
#include "Resource/StbImageLoader.h"
#include "Resource/Texture.h"
#include <Resource/stb_image.h>

namespace ToyEngine {
    const std::string VERTEX_SHADER_PATH = "Shaders/ShaderX.glsl";
    const std::string FRAGMENT_SHADER_PATH = "Shaders/FragmentShader.glsl";


    void RenderSystem::tick()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float elapsedTime = glfwGetTime();
        float greenColor = (sin(elapsedTime) / 2.0f )+ 0.5f;
        GLint uniformLocation = glGetUniformLocation(mShaderProgram, "colorFromTime");
        glUseProgram(mShaderProgram);
        glUniform4f(uniformLocation, 0.0f, greenColor, 0.0f, 1.0f);

        //glBindTexture(GL_TEXTURE_2D, mTexture);
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(mWindow.get());
        glfwPollEvents();
    }

    void RenderSystem::init(WindowPtr window) {
        mWindow = window;


        // generate buffers
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mGeneratedBuffer);
        glGenBuffers(1, &mEBO);

        glBindVertexArray(mVAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, mGeneratedBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);


        initShader();

        
        // must init shader first!!
        initTexture();
    }

    void RenderSystem::initTexture() {
        glGenTextures(1, &mTexture);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture);
        // Add more texture here.


        //Configuration
        //=================================================================================
        // what if the texture coordinate is over 1.0?
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // For GL_CLAMP_TO_BORDER
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        //float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        //=================================================================================
        // filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //=================================================================================
        // set image data
        stbi_set_flip_vertically_on_load(true);

        ToyEngine::StbImageLoader stbLoader;
        ToyEngine::ImageLoader* loader = &stbLoader;
        int width, height, channels;
        auto data = loader->getImageFrom("Resources/Images/FunnyPicture.jpg", &width, &height, &channels);
        auto texture = ToyEngine::Texture(data, (unsigned int)width, (unsigned int)height, (unsigned int)channels, (unsigned int)channels, 0u);

        if (data) {
            unsigned int size;
            auto data_c = texture.getData();
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_c);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);

            glUseProgram(mShaderProgram);
            glUniform1f(glGetUniformLocation(mShaderProgram, "texture1"), mTexture);
        }
        else {
            std::cerr << "????????????????"<<std::endl;
        }

        // don't forget to free image
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
