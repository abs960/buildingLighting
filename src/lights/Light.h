#pragma once

#include <glm/glm.hpp>
#include "../shaders/Shader.h"

class Light {
public:
	virtual void updateShader(Shader* shader) = 0;

	glm::vec3 getColor();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();

	void setColor(glm::vec3 color);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);

protected:
	glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};


