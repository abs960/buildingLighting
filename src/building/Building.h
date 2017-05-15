#pragma once

#include <string>
#include <vector>

#include "WallObject.h"
#include "interiorObjects/DecorativeObject.h"
#include "interiorObjects/LightSource.h"
#include "../shaders/Shader.h"

class Building {
public:
	void updateShader(Shader* shader);
	void draw(Shader* shader);

	void save(std::string path);
	void load(std::string path);

	void setObjects(std::vector<InteriorObject*> objects);
	void pushObject(InteriorObject* object);
	std::vector<InteriorObject*> getObjects();
	InteriorObject* getObject(int num);

	void setWalls(std::vector<WallObject*> walls);
	void addWall(WallObject* wall);
	std::vector<WallObject*> getWalls();
	WallObject* getWall(int num);

protected:
	std::vector<InteriorObject*> objects;
	std::vector<WallObject*> walls;
};


