#pragma once

#include<memory>
#include<vector>
#include "../Renderer/RenderSystem.h"
#include<glad/glad.h>
#include "GLFW/glfw3.h"

namespace ToyEngine {

	using WindowPtr = std::shared_ptr<GLFWwindow>;

	class MyEngine
	{
		WindowPtr& mWindow;
		std::shared_ptr<RenderSystem> mRenderSystem;

		public:
			MyEngine(WindowPtr& window) :mWindow(window) {};

			void tick();

			
	};
}


