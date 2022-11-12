#include "Renderer/RenderComponent.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLFW/glfw3.h"
#include "Renderer/Camera.h"
#include <functional>

namespace ToyEngine {
	void RenderComponent::tick()
	{
        if (mtextureDataPtr) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mTextureIndex);
        }
        mShader->use();

        // Testing transform uniform
        auto model = glm::mat4(1.0f);
        if (true) {
            // rotation need to be improved
            auto model_rotate = glm::rotate(model, (float)glfwGetTime() * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            auto model_translate = glm::translate(model, mWorldPos);
            model = model_translate * model_rotate;
        }
        else {
            auto model_translate = glm::translate(model, mWorldPos);
            model = model_translate;
        }
        mShader->setUniform("model", model);

        

        auto view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = mCamera->GetViewMatrix();
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        mShader->setUniform("view", view);

        mShader->setUniform("normalMat", glm::transpose(glm::inverse(view * model)));

        auto projection = glm::mat4(1);
        projection = glm::perspective(glm::radians(mCamera->mZoom), 800.0f / 600.0f, 0.1f, 100.0f);
        mShader->setUniform("projection", projection);

        glBindVertexArray(mVAOIndex);
        if (mIndicesPtr) {
            glDrawElements(GL_TRIANGLES, mIndicesPtr->size(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        
        glBindVertexArray(0);
	}

	void RenderComponent::init()
	{

        // generate buffers
        glGenVertexArrays(1, &mVAOIndex);
        glGenBuffers(1, &mVBOIndex);
        if (mIndicesPtr) {
            glGenBuffers(1, &mEBOIndex);
        }
        
        glBindVertexArray(mVAOIndex);

        glBindBuffer(GL_ARRAY_BUFFER, mVBOIndex);
        glBufferData(GL_ARRAY_BUFFER, mVertexDataPtr->size() * sizeof(VertexDataElementType), mVertexDataPtr->data(), GL_STATIC_DRAW);

        if (mIndicesPtr) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBOIndex);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesPtr->size() * sizeof(IndexDataElementType), mIndicesPtr->data(), GL_STATIC_DRAW);
        }



        if (mtextureDataPtr) {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        else if(!mtextureDataPtr && !mIsWithNormal) {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        else if(!mtextureDataPtr && mIsWithNormal) {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
	}




}
