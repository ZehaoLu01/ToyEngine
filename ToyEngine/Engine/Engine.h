#pragma once

#include<memory>
#include<vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../Renderer/RenderSystem.h"

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

	private:
		shared_ptr<RenderSystem> mRenderSystem = make_shared<RenderSystem>();

		WindowPtr mWindow;
	};
}


