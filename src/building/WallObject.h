#pragma once

#include "../modeling/Mesh.h"

class WallObject {
public:
	void updateShader(Shader* shader);
	void draw(Shader* shader);

protected:
	int width;
	int height;
	int length;

	Mesh mesh;
	Texture texture;
};


