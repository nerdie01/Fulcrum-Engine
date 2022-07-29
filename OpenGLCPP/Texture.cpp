#include <iostream>
#include <fstream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>

#include "Texture.h"

unsigned char* textureBuffer;
GLuint texture;
int width, height, numChannels;

void Texture::init(const char* path) {
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	textureBuffer = stbi_load(path, &width, &height, &numChannels, 0);

	if (!textureBuffer) {
		std::cout << "Failed to load texture " << path << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	std::cout << "Successfully loaded texture " << path << std::endl;

	stbi_image_free(textureBuffer);
}

GLuint Texture::getTextureID() {
	return texture;
}

void Texture::set(GLuint slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture);
}