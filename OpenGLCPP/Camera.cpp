#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/glm.hpp>

#include "Camera.h"
#include "Shader.h"

glm::mat4 viewport;

void Camera::init() {
	viewport = glm::mat4(1.0f);
}

void Camera::render(glm::mat4* projection, Shader& shader) {
	viewport = glm::translate(viewport, glm::vec3(0.0f, 0.0f, -3.0f));

	glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgram(), "viewport"), 1, GL_FALSE, &viewport[0][0]);
	shader.setValue("projection", projection);
}