#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {
public:
	virtual void updateShader(Shader* shader);

	glm::vec3 getDirection();
	float getCutOff();
	float getOuterCutOff();

	void setDirection(glm::vec3 direction);
	void setCutOff(float cutOff);
	void setOuterCutOff(float outerCutOff);

protected:
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;
};


