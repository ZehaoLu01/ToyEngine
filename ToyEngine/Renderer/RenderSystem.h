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
				float vertexData[20] = {
					 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
					 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
					-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
					-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
				};


				unsigned int indices[6] = {  // note that we start from 0!
					0, 1, 3,   // first triangle
					1, 2, 3    // second triangle
				};
				GLuint mGeneratedBuffer;
				GLuint mVAO;
				GLuint mShaderProgram;
				GLuint mEBO;
				GLuint mTexture;
				WindowPtr mWindow;

				void initShader();
				void initTexture();
	};
}


