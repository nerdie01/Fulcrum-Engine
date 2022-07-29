#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Shader.h"

class Camera
{
public:
	void init();
	void render(glm::mat4* projection, Shader& shader);
//private:
//	glm::mat4 viewport;
};

