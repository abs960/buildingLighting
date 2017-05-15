#pragma once

#include "../../modeling/Model.h"
#include "../../shaders/Shader.h"

class InteriorObject {
public:
	virtual void updateShader(Shader* shader) = 0;
	virtual void draw(Shader* shader);

	void loadModel(const char* path);
	void setModel(Model model);
	Model getModel();

protected:
	Model model;

};


