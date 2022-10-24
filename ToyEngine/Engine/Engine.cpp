#include "Engine.h"

namespace ToyEngine{
	void MyEngine::tick()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Logic Tick
		
		// Render Tick

		glfwSwapBuffers(mWindow.get());
		mRenderSystem->tick();
		glfwPollEvents();
	}


}
