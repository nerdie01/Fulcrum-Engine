#include <iostream>
#include <fstream>
#include <sstream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/glm.hpp>

#include "Shader.h"

GLuint shaderProgram, vertexShader, fragmentShader;

GLuint Shader::getShaderProgram() {
	return shaderProgram;
}

void Shader::init(const char* vertexShaderPath, const char* fragmentShaderPath) {
	std::string vertexShaderSourceCode = getShader(vertexShaderPath).c_str();
	const char* vertexShaderSource = vertexShaderSourceCode.c_str();
	std::cout << "Found valid GLSL file for GL_VERTEX_SHADER." << std::endl;

	std::string fragmentShaderSourceCode = getShader(fragmentShaderPath).c_str();
	const char* fragmentShaderSource = fragmentShaderSourceCode.c_str();
	std::cout << "Found valid GLSL file for GL_FRAGMENT_SHADER." << std::endl;

	vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource, "GL_VERTEX_SHADER");
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, "GL_FRAGMENT_SHADER");

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

#pragma region ShaderSetValue

void Shader::setValue(const char* name, bool value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), (int)value);
}

void Shader::setValue(const char* name, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setValue(const char* name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setValue(const char* name, const glm::vec2& value) {
	glUniform2fv(glGetUniformLocation(shaderProgram, name), 1, &value[0]);
}

void Shader::setValue(const char* name, const glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, &value[0]);
}

void Shader::setValue(const char* name, const glm::vec4& value) {
	glUniform4fv(glGetUniformLocation(shaderProgram, name), 1, &value[0]);
}

void Shader::setValue(const char* name, const glm::mat2& value) {
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setValue(const char* name, const glm::mat3& value) {
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}
void Shader::setValue(const char* name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}

#pragma endregion

GLuint Shader::getValue(const char* name) {
	return glGetUniformLocation(shaderProgram, name);
}

std::string Shader::getShader(const char* path) {
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