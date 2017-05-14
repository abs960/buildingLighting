#pragma once

#include "../Camera.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ViewScene : public Scene {
public:
	ViewScene(int windowWidth, int windowHeight);

	virtual void load();
	virtual void handleEvents();
	virtual void updateShader(Shader* shader);
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
	static void mouseCallback(GLFWwindow *window, double xPos, double yPos);

protected:
	static Camera camera;
	static GLfloat lastX, lastY;
	static bool firstMouse;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	int windowWidth;
	int windowHeight;
};


