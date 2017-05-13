#include "DirectionalLight.h"

void DirectionalLight::updateShader(Shader *shader) {
	shader->use();

	GLuint programId = shader->getProgram();

	glUniform3f(glGetUniformLocation(programId, connectField(DIRECTIONAL_LIGHT, COLOR)),
				color.r, color.g, color.b);
	glUniform3f(glGetUniformLocation(programId, connectField(DIRECTIONAL_LIGHT, DIRECTION)),
				direction.x, direction.y, direction.z);
	glUniform3f(glGetUniformLocation(programId, connectField(DIRECTIONAL_LIGHT, AMBIENT)),
				ambient.r, ambient.g, ambient.b);
	glUniform3f(glGetUniformLocation(programId, connectField(DIRECTIONAL_LIGHT, DIFFUSE)),
				diffuse.r, diffuse.g, diffuse.b);
	glUniform3f(glGetUniformLocation(programId, connectField(DIRECTIONAL_LIGHT, SPECULAR)),
				specular.r, specular.g, specular.b);
}

glm::vec3 DirectionalLight::getDirection() {
	return direction;
}

void DirectionalLight::setDirection(glm::vec3 direction) {
	this->direction = direction;
}
