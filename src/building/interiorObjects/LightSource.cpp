#include "LightSource.h"

void LightSource::updateShader(Shader *shader) {
	light->updateShader(shader);
}

void LightSource::setLight(Light *light) {
	this->light = light;
}

Light *LightSource::getLight() {
	return light;
}
