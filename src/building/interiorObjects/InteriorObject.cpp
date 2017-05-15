#include "InteriorObject.h"

void InteriorObject::draw(Shader *shader) {
	model.draw(*shader);
}

void InteriorObject::loadModel(const char* path) {
	model = Model(path);
}

void InteriorObject::setModel(Model model) {
	this->model = model;
}

Model InteriorObject::getModel() {
	return model;
}
