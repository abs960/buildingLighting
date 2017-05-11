#include "Texture.h"

Texture Texture::load(std::string path) {
	Texture texture = Texture();
	texture.path = path;

	glGenTextures( 1, &texture.id );

	int width, height;

	unsigned char *image = SOIL_load_image( path.c_str( ), &width, &height, 0, SOIL_LOAD_RGB );

	// Assign texture to ID
	glBindTexture( GL_TEXTURE_2D, texture.id );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	glGenerateMipmap( GL_TEXTURE_2D );

	// Parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture( GL_TEXTURE_2D, 0 );
	SOIL_free_image_data( image );

	return texture;
}

Texture Texture::load(std::string localDirectory, std::string relativePath) {
	return load(localDirectory + '/' + relativePath);
}

void Texture::setType(std::string type) {
	this->type = type;
}

std::string Texture::getType(){
	return type;
}

GLuint Texture::getId() {
	return id;
}

aiString Texture::getPath() {
	return path;
}

Texture::Texture() {}