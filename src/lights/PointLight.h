#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	virtual void updateShader(Shader* shader);

	glm::vec3 getPosition();
	float getConstantCoef();
	float getLinearCoef();
	float getQuadraticCoef();

	void setPosition(glm::vec3 position);
	void setConstantCoef(float constantCoef);
	void setLinearCoef(float linearCoef);
	void setQuadraticCoef(float quadraticCoef);

protected:
	glm::vec3 position;
	float constantCoef;
	float linearCoef;
	float quadraticCoef;

};


