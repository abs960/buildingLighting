#include "Window.h"
#include <vector>

int main() {
	const int startWidth = 640;
	const int startHeight = 480;
	Window wnd = Window(startWidth, startHeight, "WORKING_TITLE");

	std::vector<Scene*> scenes;
	Scene* vs = new ViewScene(startWidth, startHeight);
	scenes.push_back(vs);

	wnd.setActiveScenes(scenes);

	wnd.run();

	return 0;
}