#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer/Camera.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Resource/Texture.h"
#include "Renderer/Shader.h"
#include "UI/View/ImGuiMenu.h"

namespace ToyEngine{
	using WindowPtr = std::shared_ptr<GLFWwindow>;
	class RenderComponent;
	class RenderSystem {
		public:
			void tick();
			void drawGridLine(glm::highp_mat4& projection);
			void drawCoordinateIndicator(glm::highp_mat4& projection, glm::vec3 position);
			void init(WindowPtr window, std::shared_ptr<Camera> camera);
			void setupImGUI();
			std::vector<std::shared_ptr<RenderComponent>> loadModel(std::string path, std::shared_ptr<Shader> shader);
		private:
			WindowPtr mWindow;
			std::shared_ptr<Camera> mCamera;
			std::string mDirectory;

			//testing
			std::vector<std::shared_ptr<RenderComponent>> mRenderComponents;
			std::vector<Texture> mLoadedTextures;
			float lastFrameTime = 0.0f;
			std::vector<float> mGridPoints;
			void processNode(aiNode* node, const aiScene* scene, std::shared_ptr<Shader> shader);
			std::shared_ptr<RenderComponent> processMesh(aiMesh* mesh, const aiScene* scene);
			std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
			TextureType ConvertTextureType(aiTextureType type);
			GLenum convertChannelsToFormat(unsigned int channels);

			GLuint mGridVBOIndex;
			GLuint mGridVAOIndex;
			std::shared_ptr<Shader> mGridShader;
			glm::vec3 mGridLineColor = glm::vec3(255, 0, 0);
	};
}


