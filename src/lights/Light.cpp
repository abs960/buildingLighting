#include "Light.h"

glm::vec3 Light::getColor() {
	return color;
}

glm::vec3 Light::getAmbient() {
	return ambient;
}

glm::vec3 Light::getDiffuse() {
	return diffuse;
}

glm::vec3 Light::getSpecular() {
	return specular;
}

void Light::setColor(glm::vec3 color) {
	this->color = color;
}

void Light::setAmbient(glm::vec3 ambient) {
	this->ambient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse) {
	this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec3 specular) {
	this->specular = specular;
}
