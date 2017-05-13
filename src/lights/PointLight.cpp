#include "PointLight.h"

void PointLight::updateShader(Shader *shader) {
	shader->use();

	GLuint programId = shader->getProgram();
	int pointLightCount = shader->getPointLightCount();

	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, COLOR)),
				color.r, color.g, color.b);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, POSITION)),
				position.x, position.y, position.z);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, AMBIENT)),
				ambient.r, ambient.g, ambient.b);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, DIFFUSE)),
				diffuse.r, diffuse.g, diffuse.b);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, SPECULAR)),
				specular.r, specular.g, specular.b);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, CONSTANT)),
				constantCoef);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, LINEAR)),
				linearCoef);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(POINT_LIGHT, pointLightCount, QUADRATIC)),
				quadraticCoef);

	shader->incPointLightCount();
}

glm::vec3 PointLight::getPosition() {
	return position;
}

float PointLight::getConstantCoef() {
	return constantCoef;
}

float PointLight::getLinearCoef() {
	return linearCoef;
}

float PointLight::getQuadraticCoef() {
	return quadraticCoef;
}

void PointLight::setPosition(glm::vec3 position) {
	this->position = position;
}

void PointLight::setConstantCoef(float constantCoef) {
	this->constantCoef = constantCoef;
}

void PointLight::setLinearCoef(float linearCoef) {
	this->linearCoef = linearCoef;
}

void PointLight::setQuadraticCoef(float quadraticCoef) {
	this->quadraticCoef = quadraticCoef;
}
