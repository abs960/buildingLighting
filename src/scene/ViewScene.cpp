#include "ViewScene.h"

// Static fields initialization
Camera ViewScene::camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat ViewScene::lastX = 0.0f, ViewScene::lastY = 0.0f;
bool ViewScene::firstMouse = true;

ViewScene::ViewScene(int windowWidth, int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

void ViewScene::load() {
	deltaTime = 0;
	lastFrame = 0;

	// TODO: work with Building class here, load models etc
}

void ViewScene::handleEvents() {
	GLfloat currentFrame = (GLfloat) glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		camera.processKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		camera.processKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		camera.processKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		camera.processKeyboard(RIGHT, deltaTime);
	}
}

void ViewScene::updateShader(Shader* shader) {
	shader->use();

	float aspect = (float)windowWidth / (float)windowHeight;
	glm::mat4 projection = glm::perspective(camera.getZoom(), aspect, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), PROJECTION), 1, GL_FALSE, glm::value_ptr(projection));

	glUniform3f(glGetUniformLocation(shader->getProgram(), VIEW_POSITION), camera.getPosition().x,
				camera.getPosition().y, camera.getPosition().z);

	glm::mat4 view = camera.getViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), VIEW), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), MODEL), 1, GL_FALSE, glm::value_ptr(model));
}

void ViewScene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

void ViewScene::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
	camera.processMouseScroll((GLfloat) xOffset, (GLfloat) yOffset);
}

void ViewScene::mouseCallback(GLFWwindow *window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = (GLfloat) xPos;
		lastY = (GLfloat) yPos;
		firstMouse = false;
	}

	GLfloat xOffset = (GLfloat) xPos - lastX;
	GLfloat yOffset = lastY - (GLfloat) yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = (GLfloat) xPos;
	lastY = (GLfloat) yPos;

	camera.processMouseMovement(xOffset, yOffset);
}
