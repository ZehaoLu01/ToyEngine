#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Engine/Engine.h"
#include <memory>


namespace ToyEngine{
	void MyEngine::tick()
	{
        float current_time = glfwGetTime();
        float delta_time = (float)glfwGetTime() - lastFrameTime;
        lastFrameTime = current_time;
        processInput(mWindow.get(), delta_time);
		//Logic Tick
		
		//Render Tick

		mRenderSystem->tick();

	}

	void MyEngine::init() {
		mMainCameraPtr = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 10.0f));

		mRenderSystem->init(mWindow, mMainCameraPtr);
	}

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void MyEngine::processInput(GLFWwindow* window, float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            mMainCameraPtr->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            mMainCameraPtr->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            mMainCameraPtr->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            mMainCameraPtr->ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            mMainCameraPtr->ProcessKeyboard(UP, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            mMainCameraPtr->ProcessKeyboard(DOWN, deltaTime);
        }
    }

}
