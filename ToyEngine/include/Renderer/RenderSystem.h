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
#include "../../submodule/FileExplorer/imfilebrowser.h"
#include "Engine/Component.h"
#include <entt/entity/registry.hpp>
#include "../Engine/Scene.h"


namespace ToyEngine{
	using WindowPtr = std::shared_ptr<GLFWwindow>;
	class RenderSystem {
		public:
			//void tick();
			void afterDraw();
			void preDraw();
			void drawGridLine();
			void drawCoordinateIndicator(glm::vec3 position);
			void drawMesh(const TransformComponent& transform, const MeshComponent& mesh, TextureComponent textures);
			void drawImGuiMenu();
			void initGrid();
			void init(WindowPtr window, std::shared_ptr<Camera> camera, entt::registry& registry);
			void setupImGUI();
			entt::entity loadModel(std::string path, entt::registry& registry, entt::entity parent);
			static RenderSystem instance;

		private:
			WindowPtr mWindow;
			std::shared_ptr<Camera> mCamera;
			std::string mDirectory;

			//testing
			//std::vector<std::shared_ptr<RenderComponent>> mRenderComponents;
			std::vector<Texture> mLoadedTextures;
			float lastFrameTime = 0.0f;
			std::vector<float> mGridPoints;
			void bindSiblings(entt::registry& registry, entt::entity curr, entt::entity& prev);
			entt::entity processNode(aiNode* node, const aiScene* scene, entt::registry& registry, entt::entity parent);
			entt::entity processMesh(aiMesh* mesh, const aiScene* scene, entt::registry& registry, entt::entity parent);
			std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
			TextureType ConvertTextureType(aiTextureType type);
			GLenum convertChannelsToFormat(unsigned int channels);

			GLuint mGridVBOIndex;
			GLuint mGridVAOIndex;
			std::shared_ptr<Shader> mGridShader;
			std::shared_ptr<Shader> mActiveShader;

			glm::vec3 mGridLineColor = glm::vec3(255, 0, 0);
	};
}


