#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace ToyEngine {
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // Default camera values
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;


    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class Camera
    {
    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float mYaw = -90.0f;
        float mPitch = 0.0f;

        // camera options
        float mMovementSpeed;
        float mMouseSensitivity;
        float mZoom;
        
        bool mFirstMouse = true;

        float mLastCursorX = 0.0f;
        float mLastCursorY = 0.0f;

        // constructor with vectors
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mZoom(ZOOM)
        {
            Position = position;
            WorldUp = up;
            mYaw = yaw;
            mPitch = pitch;
            updateCameraVectors();
        }
        // constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mZoom(ZOOM)
        {
            Position = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
            mYaw = yaw;
            mPitch = pitch;
            updateCameraVectors();
        }

        Camera() = default;

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(Position, Position + Front, Up);
        }

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(Camera_Movement direction, float deltaTime)
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
        void ProcessMouseMovement(double xposIn, double yposIn, GLboolean constrainPitch = true)
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
        void ProcessMouseScroll(float yoffset)
        {
            mZoom -= (float)yoffset;
            if (mZoom < 1.0f)
                mZoom = 1.0f;
            if (mZoom > 45.0f)
                mZoom = 45.0f;
        }



    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors()
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
    };

}

