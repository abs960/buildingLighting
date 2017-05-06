#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
private:
	
	GLuint program;

	GLuint createShader(GLenum shaderType, const GLchar* shaderCode) {
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

	std::string getShaderTypeName(GLenum shaderType) {
		std::string name;

		switch (shaderType) {
			case GL_COMPUTE_SHADER: name = "COMPUTE"; break;
			case GL_VERTEX_SHADER: name = "VERTEX"; break;
			case GL_TESS_CONTROL_SHADER: name = "TESS_CONTROL"; break;
			case GL_TESS_EVALUATION_SHADER: name = "TESS_EVALUATION"; break;
			case GL_GEOMETRY_SHADER: name = "GEOMETRY"; break;
			case GL_FRAGMENT_SHADER: name = "FRAGMENT"; break;
			default: name = "OTHER"; break;
		}

		return name;
	}
	
public:
	
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
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
	
	GLuint getProgram() {
		return this->program;
	}
	
	void Use() {
		glUseProgram(this->program);
	}
};
