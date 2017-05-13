#include "Shader.h"

GLuint Shader::createShader(GLenum shaderType, const GLchar* shaderCode) {
    // infoLog is used to show text of error
    GLchar infoLog[512];
    GLint success;

    GLuint result = glCreateShader(shaderType);
    glShaderSource(result, 1, &shaderCode, NULL);
    glCompileShader(result);

    // Print compile errors if any
    glGetShaderiv(result, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(result, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << getShaderTypeName(shaderType) << "COMPILATION_FAILED" << std::endl
                  << infoLog << std::endl;
    }

    return result;
}

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
	spotLightCount = 0;
	pointLightCount = 0;

    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    // 2. Compile shaders
    GLuint vertex = createShader(GL_VERTEX_SHADER, vShaderCode);
    GLuint fragment = createShader(GL_FRAGMENT_SHADER, fShaderCode);

    GLint success;
    GLchar infoLog[512];
    // Shader Program
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into program now and are no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    vShaderFile.close();
    fShaderFile.close();
}

GLuint Shader::getProgram() {
    return this->program;
}

void Shader::use() {
    glUseProgram(this->program);
}

void Shader::incPointLightCount() {
	pointLightCount++;
}

void Shader::incSpotLightCount() {
	spotLightCount++;
}

int Shader::getPointLightCount() {
	return pointLightCount;
}

int Shader::getSpotLightCount() {
	return spotLightCount;
}

void Shader::cleanLightsCount() {
	pointLightCount = 0;
	spotLightCount = 0;
}

void Shader::applyLightsCount() {
	glUniform1i(glGetUniformLocation(program, POINT_LIGHT_COUNT), pointLightCount);
	glUniform1i(glGetUniformLocation(program, SPOTLIGHT_COUNT), spotLightCount);
}

std::string getShaderTypeName(GLenum shaderType) {
    switch (shaderType) {
        case GL_COMPUTE_SHADER: return "COMPUTE";
        case GL_VERTEX_SHADER: return "VERTEX";
        case GL_TESS_CONTROL_SHADER: return "TESS_CONTROL";
        case GL_TESS_EVALUATION_SHADER: return "TESS_EVALUATION";
        case GL_GEOMETRY_SHADER: return "GEOMETRY";
        case GL_FRAGMENT_SHADER: return "FRAGMENT";
        default: return "OTHER";
    }
}