#include "Renderer/Camera.h"

namespace ToyEngine {
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = mMovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
        if (direction == UP)
            Position += Up * velocity;
        if (direction == DOWN)
            Position += (-Up) * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void Camera::ProcessMouseMovement(double xposIn, double yposIn, GLboolean constrainPitch)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (mFirstMouse)
        {
            mLastCursorX = xpos;
            mLastCursorY = ypos;
            mFirstMouse = false;
        }

        float xoffset = xpos - mLastCursorX;
        float yoffset = mLastCursorY - ypos; // reversed since y-coordinates go from bottom to top

        mLastCursorX = xpos;
        mLastCursorY = ypos;


        xoffset *= mMouseSensitivity;
        yoffset *= mMouseSensitivity;

        mYaw += xoffset;
        mPitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (mPitch > 89.0f)
                mPitch = 89.0f;
            if (mPitch < -89.0f)
                mPitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void Camera::ProcessMouseScroll(float yoffset)
    {
        mZoom -= (float)yoffset;
        if (mZoom < 1.0f)
            mZoom = 1.0f;
        if (mZoom > 45.0f)
            mZoom = 45.0f;
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void Camera::updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
}