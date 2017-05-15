#include "StartScene.h"

void StartScene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {

}

void StartScene::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {

}

void StartScene::mouseCallback(GLFWwindow *window, double xPos, double yPos) {

}

void StartScene::load() {

}

void StartScene::handleEvents() {

}

void StartScene::updateShader(Shader *shader) {

}

void StartScene::setCallbacks(GLFWwindow *window) {
	glfwSetKeyCallback(window, StartScene::keyCallback);
	glfwSetCursorPosCallback(window, StartScene::mouseCallback);
	glfwSetScrollCallback(window, StartScene::scrollCallback);
}
