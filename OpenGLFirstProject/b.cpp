
#include <ImageProcessing/stb_image.h>
#include <iostream>
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void windowInit(GLFWwindow* &window, bool& retflag);
void gladInit(GLFWwindow* window, bool& retflag);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window=NULL;
    bool retflag=true;

    windowInit(window, retflag);
    if (!retflag)return -1;

    gladInit(window, retflag);
    if (!retflag)return -1;

    //read picture for texturing.
    int width, height, nrChannels;
    //Need to flip vertically because OpenGL assume that y axis is at the bottom of the picture, but actually many pictures have their axis at the bottom. Add this statement before loading picture.
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("FunnyPicture.jpg", &width, &height, &nrChannels, 0);
    unsigned int texture;
    if (!data) {
        std::cout << "Failed to load texture picture!" << std::endl;
    }
    else
    {
        //generate texture buffer, bind it and set data.
        
        glGenBuffers(1, &texture);
        glBindBuffer(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // build and compile our shader program
    Shader shaderProgram("vs.glsl", "fs.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,0.0f,1.0f,0.0f,0.0f,0.0f, // bottom left  
         0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,1.0f,0.0f, // bottom right 
        -0.5f,  0.5f, 0.0f,0.0f,0.0f,1.0f,0.0f,1.0f, // top left
         0.5f,  0.5f, 0.0f,1.0f,1.0f,1.0f,1.0f,1.0f  // top right   
    };

    unsigned int indices[] = {
        0,1,2,
        1,2,3
    };

    VAO vao;
    VBO vbo;
    EBO ebo;
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    vao.bind();

    vbo.inputData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    ebo.inputData(sizeof(indices), indices, GL_STATIC_DRAW);

    vbo.linkAttrPtr(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    vbo.linkAttrPtr(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vbo.linkAttrPtr(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    vao.unbind();

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.



    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        shaderProgram.useProgram();
        glBindTexture(GL_TEXTURE_2D, texture);
        vao.bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// Window Initialization
void windowInit(GLFWwindow* &window, bool& retflag)
{
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    retflag = true;
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        retflag = false;
        return;
    }
    return;
}

// GLAD Initialization
void gladInit(GLFWwindow* window, bool& retflag) {
    retflag = true;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        retflag = false;
        return;
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}