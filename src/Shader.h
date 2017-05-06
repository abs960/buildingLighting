#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

std::string getShaderTypeName(GLenum shaderType);

class Shader {
private:
    GLuint program;

    GLuint createShader(GLenum shaderType, const GLchar* shaderCode);

public:
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

    GLuint getProgram();
    void use();
};
