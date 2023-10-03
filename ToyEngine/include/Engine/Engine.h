#pragma once

#include<memory>
#include<vector>
#include <functional>
#include <entt/entity/registry.hpp>
#include <Engine/Scene.h>


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../Renderer/RenderSystem.h"
#include "Renderer/Camera.h"

namespace ToyEngine {
	class RenderSystem;
	class Scene;
	using WindowPtr = std::shared_ptr<GLFWwindow>;
	

	class MyEngine
	{
	public:
		MyEngine(WindowPtr& window) :mWindow(window){};
		void tick();
		void init();

		std::shared_ptr<Camera> getMainCamera () const {
			return mMainCameraPtr;
		}
		bool isUsingImGUI();
	private:
		float lastFrameTime = 0;
		WindowPtr mWindow;
		std::shared_ptr<ToyEngine::Scene> mActiveScene;

		void procesKeyboardEvent(GLFWwindow* window, int key, int buttonState, std::function<void()> callback);

		std::shared_ptr<Camera> mMainCameraPtr;
		bool mIsUsingImGUI = false;
		int mPrevImguiButtonState = GLFW_RELEASE;
		void processInput(float delta);
		static entt::registry mRegistry;
	};
}


