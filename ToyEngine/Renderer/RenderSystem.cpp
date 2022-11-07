#include <iostream>
#include <sstream>
#include <fstream>
#include "Renderer/RenderSystem.h"
#include "Resource/StbImageLoader.h"
#include "Resource/Texture.h"
#include <Resource/stb_image.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/RenderComponent.h"

namespace ToyEngine {

    void RenderSystem::tick()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        for (auto component : mRenderComponents) {
            component->tick();
        }
        glfwSwapBuffers(mWindow.get());
        glfwPollEvents();
    }

    void RenderSystem::init(WindowPtr window, std::shared_ptr<Camera> camera) {
        

        mWindow = window;
        mCamera = camera;
        glEnable(GL_DEPTH_TEST);

        ToyEngine::StbImageLoader stbLoader;
        ToyEngine::ImageLoader* loader = &stbLoader;

        std::shared_ptr<Shader> shaderPtr = std::make_shared<Shader>("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

        // A face render component
        // ========================================================
        int width, height, channels;
        auto textureData = loader->getImageFrom("Resources/Images/FunnyPicture.jpg", &width, &height, &channels);
        auto textureDataPtr = std::make_shared<Texture>(textureData, width, height, GL_RGB, GL_RGBA, 0);

        auto vertexDataPtr = std::make_unique<std::vector<float>>();
        *vertexDataPtr = {
                     0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        
        auto indicesDataPtr = std::make_unique<std::vector<unsigned int>>();

        *indicesDataPtr = {
                0, 1, 3,
                1, 2, 3
        };

        

        auto component =  std::make_shared<RenderComponent>(std::move(vertexDataPtr), std::move(indicesDataPtr), textureDataPtr, shaderPtr, mWindow, mCamera);
        mRenderComponents.push_back(component);

        // ========================================================

        // A light source
        vertexDataPtr = std::make_unique<std::vector<float>>();
        *vertexDataPtr = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
        };

        shaderPtr = std::make_shared<Shader>("Shaders/VertexShader.glsl", "Shaders/SingleColorFragmentShader.glsl");
        indicesDataPtr.reset();
        textureDataPtr.reset();
        component = std::make_shared<RenderComponent>(std::move(vertexDataPtr), std::move(indicesDataPtr), textureDataPtr, shaderPtr, mWindow, mCamera);
        component->setWorldPosition(glm::vec3(-0.5, -0.5, -0.5));
        mRenderComponents.push_back(component);

        
    }

}
