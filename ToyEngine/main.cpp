
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Engine.h"
#include <fstream>
#include <sstream>
#include "Resource/StbImageLoader.h"
#include "Resource/Texture.h"

using std::unique_ptr;
using ToyEngine::WindowPtr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
WindowPtr windowInit();
bool gladInit(WindowPtr window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int MAX_ROW = 20;
int MAX_COL = 20;
bool isOver = false;



int main(char* argc, char** argv)
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    WindowPtr window;

    window = windowInit();
    if (!window)return -1;

    if (!gladInit(window))return -1;

    auto engine = std::make_shared<ToyEngine::MyEngine>(window);

    engine->init();
  
    while (!glfwWindowShouldClose(window.get())) {
        engine->tick();
    }
    glfwTerminate();
    return 0;
}

// Window Initialization
WindowPtr windowInit()
{
    GLFWwindow* raw_window_ptr = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ToyRenderer", NULL, NULL);
    
    // Note that if we called glfwterminate and also use default deleter, the window pointer will be delete twice.
    // To avoid this, we should not call glfwterminate. Instead customize a deleter for shared_ptr.
    WindowPtr window(raw_window_ptr, [](GLFWwindow* window) {
        glfwDestroyWindow(window);
        });
    if (!raw_window_ptr)
    {
        std::cout << "GLFW::WINDOW_INIT, Failed to create GLFW window" << std::endl;
    }
    return window;
}



// GLAD Initialization
bool gladInit(WindowPtr window) {
    bool retflag = true;
    glfwMakeContextCurrent(window.get());
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        retflag = false;
        return retflag;
    }

    return retflag;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

}