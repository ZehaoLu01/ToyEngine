#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Engine/Engine.h"
#include <memory>
#include <imgui_impl_opengl3.h>
#include "Engine/Scene.h"

extern std::shared_ptr<ToyEngine::MyEngine> engine_globalPtr;

namespace ToyEngine{
    entt::registry MyEngine::mRegistry;


    void static scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        if (engine_globalPtr && !engine_globalPtr->isUsingImGUI()) {
            engine_globalPtr->getMainCamera()->ProcessMouseScroll(yoffset);
        }
    }

    void static cursorMoveCallback(GLFWwindow* window, double xpos, double ypos) {
        ImGuiIO& io = ImGui::GetIO();

        if (!io.WantCaptureMouse) {
            if (engine_globalPtr && !engine_globalPtr->isUsingImGUI()) {
                engine_globalPtr->getMainCamera()->ProcessMouseMovement(xpos, ypos);
            }
        } 
    }

	void MyEngine::tick()
	{
        float current_time = glfwGetTime();
        float delta_time = (float)glfwGetTime() - lastFrameTime;
        lastFrameTime = current_time;
        processInput(delta_time);

		//Logic Tick
        
		//Render Tick

        mActiveScene->update();
	}

	void MyEngine::init() {
        // Must register callback first then init imgui.
        // See onenote for details
        glfwSetScrollCallback(mWindow.get(), scrollCallback);
        glfwSetCursorPosCallback(mWindow.get(), cursorMoveCallback);

		mMainCameraPtr = std::make_shared<Camera>(glm::vec3(0.0f, 10.0f, 10.0f));
        
        mActiveScene = std::make_shared<MyScene>();
        mActiveScene->init();

		RenderSystem::instance.init(mWindow, mMainCameraPtr, mActiveScene);


        glfwSetInputMode(mWindow.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
       
	}

    bool MyEngine::isUsingImGUI()
    {
        return mIsUsingImGUI;
    }

    void MyEngine::procesKeyboardEvent(GLFWwindow* window, int key, int buttonState, std::function<void()> callback) {
        if (glfwGetKey(window, key) == buttonState) {
            callback();
        }
    }

    void MyEngine::processInput(float delta_time) {
        //Can this be simplifeid? Button up and down event.
        procesKeyboardEvent(mWindow.get(), GLFW_KEY_G, GLFW_PRESS, [&]() {
            mPrevImguiButtonState = GLFW_PRESS;
        });

        procesKeyboardEvent(mWindow.get(), GLFW_KEY_G, GLFW_RELEASE, [&]() {
            if (mPrevImguiButtonState == GLFW_PRESS) {
                mIsUsingImGUI = !mIsUsingImGUI;
                auto targetCursorState = mIsUsingImGUI ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
                glfwSetInputMode(mWindow.get(), GLFW_CURSOR, targetCursorState);
                mPrevImguiButtonState = GLFW_RELEASE;
            }
        });

        procesKeyboardEvent(mWindow.get(), GLFW_KEY_W, GLFW_PRESS, [&]() {mMainCameraPtr->ProcessKeyboard(FORWARD, delta_time); });
        procesKeyboardEvent(mWindow.get(), GLFW_KEY_S, GLFW_PRESS, [&]() {mMainCameraPtr->ProcessKeyboard(BACKWARD, delta_time); });
        procesKeyboardEvent(mWindow.get(), GLFW_KEY_A, GLFW_PRESS, [&]() {mMainCameraPtr->ProcessKeyboard(LEFT, delta_time); });
        procesKeyboardEvent(mWindow.get(), GLFW_KEY_D, GLFW_PRESS, [&]() {mMainCameraPtr->ProcessKeyboard(RIGHT, delta_time); });
        procesKeyboardEvent(mWindow.get(), GLFW_KEY_SPACE, GLFW_PRESS, [&]() {mMainCameraPtr->ProcessKeyboard(UP, delta_time); });
        procesKeyboardEvent(mWindow.get(), GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, [&]() {mMainCameraPtr->ProcessKeyboard(DOWN, delta_time); });
        procesKeyboardEvent(mWindow.get(), GLFW_KEY_ESCAPE, GLFW_PRESS, [&]() {glfwSetWindowShouldClose(mWindow.get(), true); });
    }
}
