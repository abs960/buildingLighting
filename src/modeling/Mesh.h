#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shaders/Shader.h"
#include "Texture.h"
#include "Vertex.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

	// Render the mesh
	void Draw(Shader shader);

private:
	GLuint VAO, VBO, EBO;

	// Initializes all the buffer objects/arrays
	void setupMesh();
};


