#pragma once

#include<memory>
#include<vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../Renderer/RenderSystem.h"
#include "Renderer/Camera.h"

namespace ToyEngine {
	class RenderSystem;
	using WindowPtr = std::shared_ptr<GLFWwindow>;
	using std::shared_ptr;
	using std::make_shared;

	class MyEngine
	{
	public:
		MyEngine(WindowPtr& window) :mWindow(window) {};
		void tick();
		void init();

		std::shared_ptr<Camera> getMainCamera () const {
			return mMainCameraPtr;
		}
		
	private:
		shared_ptr<RenderSystem> mRenderSystem = make_shared<RenderSystem>();
		float lastFrameTime = 0;
		WindowPtr mWindow;

		void processInput(GLFWwindow* window, float deltaTime);

		std::shared_ptr<Camera> mMainCameraPtr;
	};
}


