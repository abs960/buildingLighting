#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <assimp/types.h>
#include "../../SOIL2/SOIL2.h"

#include <string>
#include <vector>

class Texture {
public:
	static Texture load(std::string path);
	static Texture load(std::string localDirectory, std::string relativePath);

	void setType(std::string type);

	std::string getType();
	GLuint getId();
	aiString getPath();
protected:
	Texture();

	GLuint id;
	std::string type;
	aiString path;
};