#pragma once

#include <vector>
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// My classes
#include "scene/StartScene.h"
#include "scene/ViewScene.h"
#include "scene/EditScene.h"
#include "shaders/Shader.h"
#include "modeling/Model.h"
#include "lights/PointLight.h"
#include "lights/DirectionalLight.h"
#include "lights/SpotLight.h"

#define activeScene scenes[activeSceneNum]

class Window {
public:
	Window();
	Window(int width, int height);
	Window(int width, int height, const char* title);
	Window(bool fullScreen);

	void run();

	int getWindowWidth();
	int getWindowHeight();
	const char *getWindowTitle();
	bool isFullscreen();

	std::vector<Scene*> getActiveScenes();
	Scene* getScene(int num);

	void setWindowWidth(int windowWidth);
	void setWindowHeight(int windowHeight);
	void setWindowTitle(const char* windowTitle);
	void setFullscreen(bool fullscreen);

	void setActiveScenes(std::vector<Scene*> activeScenes);
	void pushScene(Scene* scene);

	void switchActiveScene(int newActiveSceneNum);
protected:
	static const int DEFAULT_WIDTH;
	static const int DEFAULT_HEIGHT;
	static const char DEFAULT_TITLE[];

	GLFWwindow* window;

	int windowWidth;
	int windowHeight;
	const char* windowTitle;
	bool fullscreen;

	std::vector<Scene*> scenes;
	int activeSceneNum;

	int init();
	int close();

	void setCallbacks();
};


