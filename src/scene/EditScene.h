#pragma once

#include "ViewScene.h"

class EditScene : public ViewScene {
public:
	EditScene(int windowWidth, int windowHeight);

	virtual void load();
	virtual void handleEvents();
	virtual void updateShader(Shader* shader);
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
	static void mouseCallback(GLFWwindow *window, double xPos, double yPos);
};


