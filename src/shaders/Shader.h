#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ModelShader.h"

std::string getShaderTypeName(GLenum shaderType);

class Shader {
public:
	Shader(const char *vertexPath, const char *fragmentPath);

	GLuint getProgram();
	void use();

	void incPointLightCount();
	void incSpotLightCount();

	int getPointLightCount();
	int getSpotLightCount();

	void applyLightsCount();
	void cleanLightsCount();
private:
    GLuint program;
	int spotLightCount;
	int pointLightCount;

    GLuint createShader(GLenum shaderType, const char* shaderCode);
};
