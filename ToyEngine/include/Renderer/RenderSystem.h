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
#include "UI/View/ImGuiManager.h"
#include "../../submodule/FileExplorer/imfilebrowser.h"
#include "Engine/Component.h"
#include <entt/entity/registry.hpp>
#include "../Engine/Scene.h"
#include <Resource/ResourceManager.h>
#include <Renderer/SkyBox.h>


namespace ToyEngine{
	using WindowPtr = std::shared_ptr<GLFWwindow>;
	class RenderSystem {
		public:
			//void tick();
			void afterDraw();
			void preDraw();
			void drawGridLine();
			void drawCoordinateIndicator(glm::vec3 position);
			void drawMesh(const TransformComponent& transform, const MeshComponent& mesh, MaterialComponent textures);
			void drawImGuiManager();
			void drawPointLight();
			void initGrid();
			void init(WindowPtr window, std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene);
			void setupImGUI();
			entt::entity loadModel(std::string path, std::string modelName, entt::registry& registry, entt::entity parent);

			void setupTextureOfType(entt::entity entity, aiTextureType type, aiMaterial* const& pMaterial, const std::string& directory, const aiScene* scene);

			void getTexturesOfType(aiTextureType type, aiMaterial* const& pMaterial, std::vector<Texture>& vecToAdd);

			void applyLighting(Shader* shader);

			static RenderSystem instance;

			void drawSkyBox() {
				mSkyBox.render();
			}

		private:
			WindowPtr mWindow;
			std::shared_ptr<Camera> mCamera;
			std::string mDirectory;

			std::vector<Texture> mLoadedTextures;
			float lastFrameTime = 0.0f; 
			std::vector<float> mGridPoints;
			void bindSiblings(entt::registry& registry, entt::entity curr, entt::entity& prev);
			entt::entity processNode(aiNode* node, const aiScene* scene, entt::registry& registry, entt::entity parent, std::vector<Texture>& textures, const string& directory);
			entt::entity processMesh(aiMesh* mesh, const aiScene* scene, entt::registry& registry, entt::entity parent, std::vector<Texture>& textures, const string& directory);

			aiColor4D getColorFromMaterialOfType(const aiTextureType type, const aiMaterial* const pMaterial);

			GLuint mGridVBOIndex;
			GLuint mGridVAOIndex;
			std::shared_ptr<Shader> mGridShader;
			std::shared_ptr<Shader> mActiveShader;
			std::shared_ptr<Shader> mLightCubeShader;

			std::shared_ptr<Scene> mScene;

			glm::vec3 mGridLineColor = glm::vec3(255, 0, 0);
			
			ResourceManager rm;

			Texture mMissingTextureDiffuse;
			Texture mMissingTextureSpecular;

			SkyBox mSkyBox;
	};
}


