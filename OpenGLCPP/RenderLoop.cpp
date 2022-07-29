#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/glm.hpp>

#include "RenderLoop.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

GLuint shaderID, vertexArray, vertexBuffer, elementBuffer;
GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};
float vertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

Texture texture;
Shader shader;
Camera camera;

void RenderLoop::start(GLFWwindow* window) {
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	texture.init("ground.png");
	shader.init("BasicVertexShader.glsl", "BasicFragmentShader.glsl");
	camera.init();

	shader.setValue("tex", 1);
}

void RenderLoop::update(GLFWwindow* window) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());

	glUseProgram(shader.getShaderProgram());

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(shader.getValue("transform"), 1, GL_FALSE, glm::value_ptr(transform));

	glm::mat4 projection = glm::mat4(1.0f);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	camera.render(&projection, shader);

	glBindVertexArray(vertexArray);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}