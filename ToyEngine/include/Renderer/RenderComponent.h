#pragma once
#include <vector>
#include <memory>
#include "Engine/Component.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Resource/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"


namespace ToyEngine {
	using VertexDataElementType = float;
	using VertexData = std::vector<VertexDataElementType>;
	using VertexDataPtr = std::unique_ptr<VertexData>;

	using IndexDataElementType = unsigned int;
	using IndexData = std::vector<IndexDataElementType>;
	using IndexDataPtr = std::unique_ptr<IndexData>;
	

	class RenderComponent :public Component
	{
	public:
		// Inherited via Component
		virtual void tick() override;
		virtual void init() override;

		
		
		RenderComponent() = default;

		RenderComponent(VertexDataPtr&& vertexDataPtr, IndexDataPtr&& indicesPtr, std::shared_ptr<Texture> textureDataPtr, std::shared_ptr<Shader> shader, std::shared_ptr<GLFWwindow> window)
			:mVertexDataPtr(std::move(vertexDataPtr)),
			mtextureDataPtr(textureDataPtr),
			mIndicesPtr(std::move(indicesPtr)),
			mShader(shader),
			mWindow(window)
		{
			init();
			mTextureIndex = textureDataPtr->mTextureIndex;
		}
	private:
		VertexDataPtr mVertexDataPtr;
		glm::vec3 mWorldPos = glm::vec3(1.0f,1.0f,1.0f);
		glm::vec3 mRotation_eular;

		GLuint mVBOIndex;
		GLuint mVAOIndex;
		GLuint mEBOIndex;
		GLuint mTextureIndex;
		Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
		std::shared_ptr<GLFWwindow> mWindow;

		std::shared_ptr<Texture> mtextureDataPtr;

		IndexDataPtr mIndicesPtr;
		std::shared_ptr<Shader> mShader;
		//material


		// To be removed
		void processInput(GLFWwindow* window, float deltaTime);

		float lastFrameTime=0;
	};

}

