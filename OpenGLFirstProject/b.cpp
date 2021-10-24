
#include <ImageProcessing/stb_image.h>
#include <iostream>
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Snake.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void windowInit(GLFWwindow* &window, bool& retflag);
void gladInit(GLFWwindow* window, bool& retflag);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int MAX_ROW = 100;
int MAX_COL = 100;

Snake::DIRECTION keyboardDirection = Snake::DIRECTION::UP;


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

    float tableVertices[] = {
        -6.5f,-0.5f,-12.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
        6.5f,-0.5f,-12.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
        6.5f,-0.5f,0.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
        -6.5f,-0.5f,0.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
        -6.5f, 0.5f,-12.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
        6.5f, 0.5f,-12.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
        6.5f, 0.5f,0.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
        -6.5f, 0.5f,0.5f,64.0f,191.0f,64.0f,0.0f,0.0f,
    };

    unsigned int tableIndices[] = {
        3,6,7,
        3,6,2,
        2,5,6,
        2,5,1,
        1,4,5,
        1,4,0,
        0,7,4,
        0,7,3,
        2,0,3,
        2,0,1,
        7,5,4,
        7,5,6,
    };


    float vertices[] = {
        -0.5f, -0.5f, 0.5f,0.0f,0.0f,0.0f,0.0f,0.0f, 
         0.5f, -0.5f, 0.5f,0.0f,0.0f,0.0f,0.0f,0.0f,
         0.5f, -0.5f, -0.5f,0.0f,0.0f,0.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,0.0f,0.0f,0.0f,0.0f,0.0f,
        -0.5f, 0.5f, 0.5f,0.0f,0.0f,0.0f,0.0f,0.0f,
         0.5f, 0.5f, 0.5f,0.0f,0.0f,0.0f,0.0f,0.0f,
         0.5f, 0.5f, -0.5f,0.0f,0.0f,0.0f,0.0f,0.0f,
        -0.5f, 0.5f, -0.5f,1.0f,1.0f,0.0f,0.0f,0.0f,
    };

    unsigned int indices[] = {
        0,1,2,
        0,3,2,
        3,7,6,
        3,2,6,
        2,6,5,
        2,1,5,
        1,5,4,
        1,0,4,
        0,4,7,
        0,3,7,
        4,5,6,
        4,7,6,
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

    VAO tableVAO;
    EBO tableEBO;
    VBO tableVBO;
    tableVAO.bind();

    tableVBO.inputData(sizeof(tableVertices), tableVertices, GL_STATIC_DRAW);
    tableEBO.inputData(sizeof(tableIndices), tableIndices, GL_STATIC_DRAW);
    tableVBO.linkAttrPtr(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    tableVBO.linkAttrPtr(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    tableVBO.linkAttrPtr(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    tableVAO.unbind();
    

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    
    Snake snake;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        shaderProgram.useProgram();

        // render
        // ------

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // -------------------------------------------------------------------------------
        glm::mat4 rotation = glm::mat4(1.0f);
        //rotation = glm::rotate(rotation, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shaderProgram.setUniformM4f("rotation", rotation);
        glm::mat4 model = glm::mat4(1.0f);
        model= glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        shaderProgram.setUniformM4f("model", model);
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view_t(1);
        view_t = glm::translate(view_t, glm::vec3(0.0f, -7.0f, -20.0f));
        view = view_t * view;
        shaderProgram.setUniformM4f("view", view);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.001f, 1000.0f);
        shaderProgram.setUniformM4f("projection", projection);

        glBindTexture(GL_TEXTURE_2D, texture);
        vao.bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        // -------------------------------------------------------------------------------
        model = glm::mat4(1.0f);
        rotation = glm::mat4(1.0f);
        shaderProgram.setUniformM4f("model", model);
        shaderProgram.setUniformM4f("view", view);
        shaderProgram.setUniformM4f("rotation", rotation);
        shaderProgram.setUniformM4f("projection", projection);
        tableVAO.bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        // -------------------------------------------------------------------------------
        snake.render(vao,shaderProgram);
        snake.changeDirection(keyboardDirection);
        snake.move();

        // -------------------------------------------------------------------------------
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
    glfwSetKeyCallback(window, key_callback);

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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        keyboardDirection = Snake::DIRECTION::UP;
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        keyboardDirection = Snake::DIRECTION::LEFT;
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        keyboardDirection = Snake::DIRECTION::RIGHT;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        keyboardDirection = Snake::DIRECTION::DOWN;
    }
        
}