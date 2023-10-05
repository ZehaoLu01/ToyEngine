#pragma once
#include <imgui.h>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <Resource/StbImageLoader.h>
#include "Shader.h"

namespace ToyEngine {
    class Camera;
    class SkyBox
    {
    public:
        SkyBox() = default;
        SkyBox(const std::vector<std::string>& faces, std::shared_ptr<Camera> camera);

        void render();
    private:
        void loadCubemap(const std::vector<std::string>& faces);
        void initCube();
        static float skyboxVertices[];
        GLuint mTextureId;
        GLuint mCubeVBO;
        GLuint mCubeVAO;
        Shader mShader;
        std::shared_ptr<Camera> mCamera;
    };
}

