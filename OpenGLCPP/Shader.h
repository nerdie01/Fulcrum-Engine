#pragma once
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	GLuint getShaderProgram();
	void setValue(const std::string& name, bool value);
	void setValue(const std::string& name, int value);
	void setValue(const std::string& name, float value);
private:
	std::string getShader(std::string path);
	unsigned int compileShader(GLenum type, const char* shaderSource, std::string name);
};

