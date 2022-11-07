#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer/Camera.h"

namespace ToyEngine{
	using WindowPtr = std::shared_ptr<GLFWwindow>;
	class RenderComponent;
	class RenderSystem {
		public:
			void tick();
			void init(WindowPtr window, std::shared_ptr<Camera> camera);
				
		private:
			
			WindowPtr mWindow;
			std::shared_ptr<Camera> mCamera;

			GLuint initShader();
			void initTexture();

			//testing
			std::shared_ptr<RenderComponent> mRenderComponent;

			float lastFrameTime = 0.0f;
	};
}


