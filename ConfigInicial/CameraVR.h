#pragma once

// Std. Includes
#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_MovementVR
{
	FORWARDVR,
	BACKWARDVR,
	LEFTVR,
	RIGHTVR
};

// Default camera values
const GLfloat YAWVR = -90.0f;
const GLfloat PITCHVR = 0.0f;
const GLfloat SPEEDVR = 6.0f;
const GLfloat SENSITIVTYVR = 0.25f;
const GLfloat ZOOMVR = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class CameraVR
{
public:
	// Constructor with vectors
	CameraVR(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	// Constructor with scalar values
	CameraVR(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
	{
		this->position = glm::vec3(posX, posY, posZ);
		this->worldUp = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, this->position + this->front, this->up);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_MovementVR direction, GLfloat deltaTime)
	{
		GLfloat velocity = this->movementSpeed * deltaTime;

		if (direction == FORWARDVR)
		{

			glm::vec3 upFront = this->position + this->front * velocity;

			if ((upFront).z > -5.0f && (upFront).z <5.0f && (upFront).x>-5.0f && (upFront).x<5.0f) {
				this->position += this->front * velocity;

				this->position.y = 0;

			}


		}

		if (direction == BACKWARDVR)
		{
			glm::vec3 backFront = this->position - this->front * velocity;

			if ((backFront).z > -5.0f && (backFront).z <5.0f && (backFront).x>-5.0f && (backFront).x < 5.0f) {
				this->position -= this->front * velocity;

				this->position.y = 0;

			}

			
		}

		if (direction == LEFTVR)
		{
			glm::vec3 lRight = this->position - this->front * velocity;

			if ((lRight).z > -5.0f && (lRight).z <5.0f && (lRight).x>-5.0f && (lRight).x < 5.0f) {
				this->position -= this->right * velocity;
				this->position.y = 0;
			}

			
		}

		if (direction == RIGHTVR)
		{
			glm::vec3 rRight = this->position + this->front * velocity;
			if ((rRight).z > -5.0f && (rRight).z <5.0f && (rRight).x>-5.0f && (rRight).x < 5.0f) {
				this->position += this->right * velocity;
				this->position.y = 0;
			}
			
		}
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= this->mouseSensitivity;
		yOffset *= this->mouseSensitivity;

		this->yaw += xOffset;
		this->pitch += yOffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (this->pitch > 89.0f)
			{
				this->pitch = 89.0f;
			}

			if (this->pitch < -89.0f)
			{
				this->pitch = -89.0f;
			}
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yOffset)
	{

	}

	GLfloat GetZoom()
	{
		return this->zoom;
	}

	glm::vec3 GetPosition()
	{
		return this->position;
	}

	glm::vec3 GetFront()
	{
		return this->front;
	}

private:
	// Camera Attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;

	// Camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;

	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
};