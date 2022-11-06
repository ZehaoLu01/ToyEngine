#include "Renderer/RenderComponent.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLFW/glfw3.h"

namespace ToyEngine {
	void RenderComponent::tick()
	{
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureIndex);

        glUseProgram(mShaderProgramIndex);

        // Testing transform uniform
        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        GLuint modelLoc = glGetUniformLocation(mShaderProgramIndex, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        auto view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        GLuint viewLoc = glGetUniformLocation(mShaderProgramIndex, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        auto projection = glm::mat4(1);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        GLuint projectionLoc = glGetUniformLocation(mShaderProgramIndex, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //glBindTexture(GL_TEXTURE_2D, mTexture);
        glBindVertexArray(mVAOIndex);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
	}

	void RenderComponent::init()
	{
        // generate buffers
        glGenVertexArrays(1, &mVAOIndex);
        glGenBuffers(1, &mVBOIndex);
        glGenBuffers(1, &mEBOIndex);

        glBindVertexArray(mVAOIndex);

        glBindBuffer(GL_ARRAY_BUFFER, mVBOIndex);
        glBufferData(GL_ARRAY_BUFFER, mVertexDataPtr->size() * sizeof(VertexDataElementType), mVertexDataPtr->data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBOIndex);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesPtr->size() * sizeof(IndexDataElementType), mIndicesPtr->data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
	}

}
