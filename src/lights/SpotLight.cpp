#include "SpotLight.h"

void SpotLight::updateShader(Shader* shader) {
	shader->use();

	GLuint programId = shader->getProgram();
	int spotlightCount = shader->getSpotLightCount();

	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, COLOR)), color.r, color.g, color.b);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, POSITION)), position.x, position.y, position.z);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, DIRECTION)), direction.x, direction.y, direction.z);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, AMBIENT)), ambient.r, ambient.g, ambient.b);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, DIFFUSE)), diffuse.r, diffuse.g, diffuse.b);
	glUniform3f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, SPECULAR)), specular.r, specular.g, specular.b);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, CONSTANT)), constantCoef);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, LINEAR)), linearCoef);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, QUADRATIC)), quadraticCoef);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, CUTOFF)), cutOff);
	glUniform1f(glGetUniformLocation(programId, connectFieldAndCount(
			SPOTLIGHT, spotlightCount, OUTER_CUTOFF)), outerCutOff);

	shader->incSpotLightCount();
}

glm::vec3 SpotLight::getDirection() {
	return direction;
}

float SpotLight::getCutOff() {
	return cutOff;
}

float SpotLight::getOuterCutOff() {
	return outerCutOff;
}

void SpotLight::setDirection(glm::vec3 direction) {
	this->direction = direction;
}

void SpotLight::setCutOff(float cutOff) {
	this->cutOff = cutOff;
}

void SpotLight::setOuterCutOff(float outerCutOff) {
	this->outerCutOff = outerCutOff;
}
