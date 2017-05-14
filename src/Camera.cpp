#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) {
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

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt( this->position, this->position + this->front, this->up );
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime) {
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

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
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

void Camera::processMouseScroll(GLfloat xOffset, GLfloat yOffset) {}

GLfloat Camera::getZoom() {
    return this->zoom;
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

glm::vec3 Camera::getFront() {
    return this->front;
}

void Camera::updateCameraVectors() {
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