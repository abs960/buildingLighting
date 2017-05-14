#include "Scene.h"

bool Scene::keys[1024] = { false };

void Scene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if ( key >= 0 && key < 1024 ) {
		if( action == GLFW_PRESS ) {
			keys[key] = true;
		} else if( action == GLFW_RELEASE ) {
			keys[key] = false;
		}
	}
}

void Scene::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {}

void Scene::mouseCallback(GLFWwindow *window, double xPos, double yPos) {}
