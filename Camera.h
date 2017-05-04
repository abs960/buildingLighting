#pragma once

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away
// from window-system specific input methods
enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const GLfloat YAW		= -90.0f;	// left/right
const GLfloat PITCH		=  0.0f;	// up/down
const GLfloat SPEED		=  5.0f;
const GLfloat SENSIVITY	=  0.15f;
const GLfloat ZOOM		=  45.0f;

// An camera class that processes input and calculates the corresponding Eular Angles,
// Vectors and Matrices for use in OpenGL
class Camera {
public:
	Camera(
			glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ),
			glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ),
			GLfloat yaw = YAW,
			GLfloat pitch = PITCH
		   )
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		
		this->front = glm::vec3(0.0f, 0.0f, -1.0f);
		this->movementSpeed = SPEED;
		this->mouseSensitivity = SENSIVITY;
		this->zoom = ZOOM;
		this->updateCameraVectors();
	}
	
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() {
		return glm::lookAt( this->position, this->position + this->front, this->up );
	}
	
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of
	// camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime) {
		GLfloat velocity = this->movementSpeed * deltaTime;

		switch (direction) {
			case FORWARD:
				this->position += this->front * velocity;
				break;
			case BACKWARD:
				this->position -= this->front * velocity;
				break;
			case LEFT:
				this->position -= this->right * velocity;
				break;
			case RIGHT:
				this->position += this->right * velocity;
				break;
			case UP:
				this->position += this->up * velocity;
				break;
			case DOWN:
				this->position -= this->up * velocity;
		}
	}
	
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = GL_TRUE) {
		xOffset *= this->mouseSensitivity;
		yOffset *= this->mouseSensitivity;
		
		this->yaw += xOffset;
		this->pitch += yOffset;
		
		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch) {
			if (this->pitch > 89.0f) {
				this->pitch = 89.0f;
			}
			if (this->pitch < -89.0f) {
				this->pitch = -89.0f;
			}
		}
		
		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}
	
	GLfloat GetZoom() {
		return this->zoom;
	}
	
	glm::vec3 GetPosition() {
		return this->position;
	}
	
	glm::vec3 GetFront() {
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
	void updateCameraVectors() {
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = (float) (cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)));
		front.y = (float) (sin(glm::radians(this->pitch)));
		front.z = (float) (sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)));
		this->front = glm::normalize(front);
		// Also re-calculate the Right and Up vector

		// Normalize the vectors, because their length gets closer to 0 the more you
		// look up or down which results in slower movement.
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
};

