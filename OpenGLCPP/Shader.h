#pragma once
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/glm.hpp>

class Shader
{
public:
	GLuint getShaderProgram();
	void init(const char* vertexShaderPath, const char* fragmentShaderPath);
	void setValue(const char* name, bool value);
	void setValue(const char* name, int value);
	void setValue(const char* name, float value);
	void setValue(const char* name, const glm::vec2& value);
	void setValue(const char* name, const glm::vec3& value);
	void setValue(const char* name, const glm::vec4& value);
	void setValue(const char* name, const glm::mat2& value);
	void setValue(const char* name, const glm::mat3& value);
	void setValue(const char* name, const glm::mat4& value);
	GLuint getValue(const char* name);
private:
	std::string getShader(const char* path);
	unsigned int compileShader(GLenum type, const char* shaderSource, std::string name);
};

