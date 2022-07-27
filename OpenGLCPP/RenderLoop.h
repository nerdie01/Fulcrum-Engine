#pragma once

#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class RenderLoop
{
public:
	void start(GLFWwindow* window);
	void update(GLFWwindow* window);
	std::string getShader(std::string path);
	unsigned int compileShader(GLenum type, const char* shaderSource, std::string name);
};

