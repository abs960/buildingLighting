#include "Building.h"

void Building::updateShader(Shader *shader) {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->updateShader(shader);
	}

	for (int i = 0; i < walls.size(); i++) {
		walls[i]->updateShader(shader);
	}
}

void Building::draw(Shader *shader) {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->draw(shader);
	}

	for (int i = 0; i < walls.size(); i++) {
		walls[i]->draw(shader);
	}
}

void Building::save(std::string path) {
	// TODO: use boost to serialize Building
}

void Building::load(std::string path) {
	// TODO: use boost to deserialize Building
}

void Building::setObjects(std::vector<InteriorObject *> objects) {
	this->objects = objects;
}

void Building::pushObject(InteriorObject *object) {
	objects.push_back(object);
}

std::vector<InteriorObject *> Building::getObjects() {
	return objects;
}

InteriorObject *Building::getObject(int num) {
	return objects[num];
}

void Building::setWalls(std::vector<WallObject *> walls) {
	this->walls = walls;
}

void Building::addWall(WallObject *wall) {
	walls.push_back(wall);
}

std::vector<WallObject *> Building::getWalls() {
	return walls;
}

WallObject *Building::getWall(int num) {
	return walls[num];
}
