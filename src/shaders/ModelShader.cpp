#include "ModelShader.h"

const GLchar* connectField(const char* structName, const char* fieldName) {
	std::string s = std::string(structName) + "." + std::string(fieldName);
	return s.c_str();
}

const GLchar *connectFieldAndCount(const char *structName, int count, const char *fieldName) {
	std::string s = std::string(structName) + "[" + std::to_string(count) + "]." + std::string(fieldName);
	return s.c_str();
}
