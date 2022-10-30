#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
namespace ToyEngine{
	using WindowPtr = std::shared_ptr<GLFWwindow>;

	class RenderSystem {
		public:
				void tick();
				void init(WindowPtr window);
		private:
				float vertexData[9] = { -0.5f, -0.5f, 0.0f,
										 0.5f, -0.5f, 0.0f,
										 0.0f,  0.5f, 0.0f };

				GLuint mGeneratedBuffer;
				GLuint mVAO;
				GLuint mShaderProgram;
				WindowPtr mWindow;

				void initShader();
	};
}


