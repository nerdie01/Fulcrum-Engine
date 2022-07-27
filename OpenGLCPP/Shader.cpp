#include <iostream>
#include <fstream>
#include <sstream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

GLuint shaderProgram, vertexShader, fragmentShader;

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	std::string vertexShaderSourceCode = getShader(vertexShaderPath).c_str();
	const char* vertexShaderSource = vertexShaderSourceCode.c_str();

	std::string fragmentShaderSourceCode = getShader(fragmentShaderPath).c_str();
	const char* fragmentShaderSource = fragmentShaderSourceCode.c_str();

	vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource, "GL_VERTEX_SHADER");
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, "GL_FRAGMENT_SHADER");

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint Shader::getShaderProgram() {
	return shaderProgram;
}

void Shader::setValue(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setValue(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setValue(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

std::string Shader::getShader(std::string path) {
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

unsigned int Shader::compileShader(GLenum type, const char* shaderSource, std::string name) {
	GLuint shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Failed to compile " << name << ": " << infoLog << std::endl;
		return -1;
	}
	std::cout << "Compiled " << name << " successfully." << std::endl;

	return shader;
}