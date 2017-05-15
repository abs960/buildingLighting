#pragma once

#include "Scene.h"

class StartScene : public Scene {
public:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
	static void mouseCallback(GLFWwindow *window, double xPos, double yPos);

	virtual void load();
	virtual void handleEvents();
	virtual void updateShader(Shader* shader);
	virtual void setCallbacks(GLFWwindow* window);
};


