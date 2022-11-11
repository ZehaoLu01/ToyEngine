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
    const glm::vec3 LIGHT_BULB_POSITION(2.0f, 2.0f, 2.0f);
    const glm::vec3 PHONG_TESTING_POSITION(0.f, 0.f, 2.f);

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
        component->init();
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
        component->init();
        component->setWorldPosition(glm::vec3(-0.5, -0.5, -0.5));
        mRenderComponents.push_back(component);


        // ========================================================

        // An object with phong
        // ========================================================
        vertexDataPtr = std::make_unique<std::vector<float>>();
        *vertexDataPtr = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        shaderPtr = std::make_shared<Shader>("Shaders/phong.vs.glsl", "Shaders/phong.fs.glsl");
        shaderPtr->use();
        shaderPtr->setUniform("spherePosition", LIGHT_BULB_POSITION);
        shaderPtr->setUniform("ambientColor", glm::vec3(0.0f, 0.0f, 1.0f));
        shaderPtr->setUniform("diffuseColor", glm::vec3(0.0f, 1.0f, 0.0f));
        shaderPtr->setUniform("specularColor", glm::vec3(1.0f, 1.0f, 0.0f));
        shaderPtr->setUniform("kAmbient", 0.3f);
        shaderPtr->setUniform("kDiffuse", 0.6f);
        shaderPtr->setUniform("kSpecular", 1.0f);
        shaderPtr->setUniform("shininess", 10.0f);

        indicesDataPtr.reset();
        textureDataPtr.reset();

        auto componentWithLight = std::make_shared<RenderComponent>(std::move(vertexDataPtr), std::move(indicesDataPtr), textureDataPtr, shaderPtr, mWindow, mCamera);
        componentWithLight->setNormalAvailablitility(true);
        componentWithLight->setWorldPosition(PHONG_TESTING_POSITION);
        componentWithLight->init();
        mRenderComponents.push_back(componentWithLight);
        
// ========================================================

        // light bulb
// ========================================================
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

        shaderPtr = std::make_shared<Shader>("Shaders/VertexShader.glsl", "Shaders/LightFragmentShader.glsl");
        shaderPtr->use();
        shaderPtr->setUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shaderPtr->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

        indicesDataPtr.reset();
        textureDataPtr.reset();

        auto lightBulb = std::make_shared<RenderComponent>(std::move(vertexDataPtr), std::move(indicesDataPtr), textureDataPtr, shaderPtr, mWindow, mCamera);
        lightBulb->init();
        lightBulb->setWorldPosition(LIGHT_BULB_POSITION);
        mRenderComponents.push_back(lightBulb);
        

    }

}
