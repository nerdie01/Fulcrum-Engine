#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>

#include "Texture.h"

class Texture
{
public:
	void init(const char* path);
	GLuint getTextureID();
	void set(GLuint slot);
};

