#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
	virtual void updateShader(Shader* shader);

	glm::vec3 getDirection();

	void setDirection(glm::vec3 direction);

protected:
	glm::vec3 direction;
};


