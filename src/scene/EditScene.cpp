#include "EditScene.h"

EditScene::EditScene(int windowWidth, int windowHeight) : ViewScene(windowWidth, windowHeight) {

}

void EditScene::load() {
	ViewScene::load();
}

void EditScene::handleEvents() {
	ViewScene::handleEvents();
}

void EditScene::updateShader(Shader *shader) {
	ViewScene::updateShader(shader);
}

void EditScene::setCallbacks(GLFWwindow *window) {
	glfwSetKeyCallback(window, EditScene::keyCallback);
	glfwSetCursorPosCallback(window, EditScene::mouseCallback);
	glfwSetScrollCallback(window, EditScene::scrollCallback);
}

void EditScene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {

}

void EditScene::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {

}

void EditScene::mouseCallback(GLFWwindow *window, double xPos, double yPos) {

}