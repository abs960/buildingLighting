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
    Camera(glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ),
           glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ),
           GLfloat yaw = YAW,
           GLfloat pitch = PITCH
    );

    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 getViewMatrix();

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of
    // camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(CameraMovement direction, GLfloat deltaTime);

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = GL_TRUE);

    GLfloat getZoom();
    glm::vec3 getPosition();
    glm::vec3 getFront();

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
    void updateCameraVectors();
};
