#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Engine.h"


namespace ToyEngine{


	void MyEngine::tick()
	{

		//Logic Tick
		
		//Render Tick

		mRenderSystem->tick();

	}

	void MyEngine::init() {
		mRenderSystem->init(mWindow);
	}
}
