#pragma once

#define POSITION_LOCATION 0
#define NORMAL_LOCATION 1
#define TEXTURE_COORDS_LOCATION 2

#define MODEL "model"
#define VIEW "view"
#define PROJECTION "projection"

#define POINT_LIGHT_COUNT "pointLightCount"
#define SPOTLIGHT_COUNT "spotLightCount"

#define VIEW_POSITION "viewPos"

#define MATERIAL "material"
#define POINT_LIGHT "pointLights"
#define SPOTLIGHT "spotLights"
#define DIRECTIONAL_LIGHT "directionalLight"

#define SHININESS "shininess"
#define COLOR "color"
#define AMBIENT "ambient"
#define DIFFUSE "diffuse"
#define SPECULAR "specular"
#define POSITION "position"
#define CONSTANT "constant"
#define LINEAR "linear"
#define QUADRATIC "quadratic"
#define CUTOFF "cutOff"
#define OUTER_CUTOFF "outerCutOff"
#define DIRECTION "direction"

#include <string>
#include <GL/glew.h>

const GLchar* connectFieldAndCount(const char* structName, int count, const char* fieldName);
const GLchar* connectField(const char* structName, const char* fieldName);