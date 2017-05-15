#include "Window.h"

const int Window::DEFAULT_WIDTH = 640;
const int Window::DEFAULT_HEIGHT = 480;
const char Window::DEFAULT_TITLE[] = "Building Lighting";

Window::Window() : Window(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE) {}

Window::Window(int width, int height) : Window(width, height, DEFAULT_TITLE) {}

Window::Window(int width, int height, const char *title) {
	this->windowWidth = width;
	this->windowHeight = height;
	this->windowTitle = title;
	this->fullscreen = false;
}

Window::Window(bool fullScreen) {
	this->fullscreen = fullScreen;
	this->windowWidth = DEFAULT_WIDTH;
	this->windowHeight = DEFAULT_HEIGHT;
	this->windowTitle = DEFAULT_TITLE;
}

void Window::run() {
	init();

	// Setup and compile our shaders
	Shader shader("resources/shaders/model.vert", "resources/shaders/model.frag");

	// TODO: move this code to Building class
	// Load models
	Model model3d("resources/models/sonic/Sonic.obj");

	// Draw in wireframe
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		// Check and call events
		glfwPollEvents();
		activeScene->handleEvents();

		// Clear the color buffer
		glClearColor(0.0f, 0.45f, 0.00f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//TODO: move this code to Building class as well

		DirectionalLight d = DirectionalLight();
		d.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		d.setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
		d.setDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		d.setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		d.setDirection(glm::vec3(-0.2f, -1.0f, -0.3f));

		d.updateShader(&shader);

//		SpotLight s = SpotLight();
//		s.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
//		s.setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
//		s.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
//		s.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
//		s.setPosition(glm::vec3(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z));
//		s.setDirection(glm::vec3(camera.getFront().x, camera.getFront().y, camera.getFront().z));
//		s.setConstantCoef(1.0f);
//		s.setLinearCoef(0.09f);
//		s.setQuadraticCoef(0.032f);
//		s.setCutOff(glm::cos(glm::radians(8.5f)));
//		s.setOuterCutOff(glm::cos(glm::radians(25.0f)));

		//s.updateShader(&shader);

		PointLight p0 = PointLight();
		p0.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		p0.setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
		p0.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
		p0.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		p0.setPosition(glm::vec3(2.3f, -1.3f, -4.0f));
		p0.setConstantCoef(0.5f);
		p0.setLinearCoef(0.09f);
		p0.setQuadraticCoef(0.032f);

		//p0.updateShader(&shader);

		PointLight p = PointLight();
		p.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		p.setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
		p.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
		p.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		p.setPosition(glm::vec3(0.7f,  0.2f,  2.0f));
		p.setConstantCoef(0.7f);
		p.setLinearCoef(0.09f);
		p.setQuadraticCoef(0.032f);

		//p.updateShader(&shader);

		shader.applyLightsCount();

		activeScene->updateShader(&shader);
		// Draw the loaded model
		model3d.draw(shader);

		shader.cleanLightsCount();

		//----------------------------------

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	close();
}

int Window::getWindowWidth() {
	return windowWidth;
}

int Window::getWindowHeight() {
	return windowHeight;
}

const char *Window::getWindowTitle() {
	return windowTitle;
}

bool Window::isFullscreen() {
	return fullscreen;
}

std::vector<Scene*> Window::getActiveScenes() {
	return scenes;
}

Scene *Window::getScene(int num) {
	return scenes[num];
}

void Window::setWindowWidth(int windowWidth) {
	this->windowWidth = windowWidth;
}

void Window::setWindowHeight(int windowHeight) {
	this->windowHeight = windowHeight;
}

void Window::setWindowTitle(const char *windowTitle) {
	this->windowTitle = windowTitle;
}

void Window::setFullscreen(bool fullscreen) {
	this->fullscreen = fullscreen;
}

void Window::setActiveScenes(std::vector<Scene *> activeScenes) {
	this->scenes = activeScenes;
}

void Window::pushScene(Scene *scene) {
	scenes.push_back(scene);
}

int Window::init() {
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);

	if (nullptr == window) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

	switchActiveScene(0);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW." << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, windowWidth, windowHeight);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	return EXIT_SUCCESS;
}

int Window::close() {
	glfwTerminate();
	return 0;
}

void Window::switchActiveScene(int newActiveSceneNum) {
	activeSceneNum = newActiveSceneNum;
	activeScene->load();
	activeScene->setCallbacks(window);
}
