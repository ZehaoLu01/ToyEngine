#pragma once
#include <vector>
#include <memory>
#include "Engine/Component.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Resource/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include <algorithm>
#include "ImGuiMenu.h"


namespace ToyEngine {
	using VertexDataElementType = float;
	using VertexData = std::vector<VertexDataElementType>;
	using VertexDataPtr = std::unique_ptr<VertexData>;

	using IndexDataElementType = unsigned int;
	using IndexData = std::vector<IndexDataElementType>;
	using IndexDataPtr = std::unique_ptr<IndexData>;
	


	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class RenderComponent :public Component
	{
	public:
		// Inherited via Component
		virtual void tick() override;
		virtual void init() override;

		void setWorldPosition(glm::vec3 position) {
			mWorldPos = position;
		}
		
		RenderComponent() = default;

		RenderComponent(VertexDataPtr&& vertexDataPtr, IndexDataPtr&& indicesPtr, std::vector<Texture> textureData, std::shared_ptr<Shader> shader, std::shared_ptr<GLFWwindow> window, std::shared_ptr<Camera> camera)
			:mVertexDataPtr(std::move(vertexDataPtr)),
			mTextures(textureData),
			mIndicesPtr(std::move(indicesPtr)),
			mShader(shader),
			mWindow(window),
			mCamera(camera)
		{
		}
		RenderComponent(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, std::shared_ptr<Shader> shader, std::shared_ptr<GLFWwindow> window, std::shared_ptr<Camera> camera)
			:mShader(shader),
			mWindow(window),
			mCamera(camera)
		{
			mVertexDataPtr = std::make_unique<VertexData>();
			for (const auto& v: vertices) {
				mVertexDataPtr->push_back(v.Position.x);
				mVertexDataPtr->push_back(v.Position.y);
				mVertexDataPtr->push_back(v.Position.z);

				mVertexDataPtr->push_back(v.Normal.x);
				mVertexDataPtr->push_back(v.Normal.y);
				mVertexDataPtr->push_back(v.Normal.z);

				mVertexDataPtr->push_back(v.TexCoords.x);
				mVertexDataPtr->push_back(v.TexCoords.y);
			}

			mIndicesPtr = std::make_unique<IndexData>();

			for (const auto& i : indices) {
				mIndicesPtr->push_back(i);
			}

			mTextures = std::vector<Texture>(textures.begin(), textures.end());
		}

		void setNormalAvailability(bool value) {
			mIsWithNormal = value;
		}

		//Get Updates from imgui.
		void updateProperties();

		void setSpotLight(bool isSpotLighting);
		bool isSpotLight();
	private:
		VertexDataPtr mVertexDataPtr;

		glm::vec3 mWorldPos = glm::vec3(1.0f,1.0f,1.0f);
		glm::vec3 mRotation_eular;
		glm::vec3 mScale;

		GLuint mVBOIndex;
		GLuint mVAOIndex;
		GLuint mEBOIndex;
		std::vector<GLuint> mTextureIndices;
		GLuint mSpecularMapIndex;

		std::shared_ptr<Camera> mCamera;
		std::shared_ptr<GLFWwindow> mWindow;

		// should be renamed.
		std::vector<Texture> mTextures;

		IndexDataPtr mIndicesPtr;
		std::shared_ptr<Shader> mShader;
		//material

		float lastFrameTime=0;

		bool mIsWithNormal = false;

		bool mIsSpotLight = false;

		ImGuiMenu& mMenuInstance = ImGuiMenu::getInstance();
	};

}

