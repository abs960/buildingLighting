#pragma once

#include "../shaders/Shader.h"
#include <GLFW/glfw3.h>

class Scene {
public:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
	static void mouseCallback(GLFWwindow *window, double xPos, double yPos);

	virtual void load() = 0;
	virtual void handleEvents() = 0;
	virtual void updateShader(Shader* shader) = 0;

protected:
	static bool keys[1024];

	//TODO: add menu and building
};


