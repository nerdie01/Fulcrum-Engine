#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "RenderLoop.h"

GLFWwindow* window;
RenderLoop renderLoop;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int initializeWindow(int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error: OpenGL/GLFW window could not be created!" << std::endl;
		glfwTerminate();
		return -2;
	}

	std::cout << "OpenGL/GLFW window created successfully" << std::endl;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error: Failed to initialize GLAD at address " << glfwGetProcAddress << std::endl;
		return -1;
	}

	renderLoop.start(window);

	std::cout << "Initialized GLAD at address " << glfwGetProcAddress << std::endl;

	std::cout << "Fulcrum Engine successfully loaded!" << std::endl;

	while (!glfwWindowShouldClose(window)) {
		renderLoop.update(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int main() {
	initializeWindow(800, 600);
	exit;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

