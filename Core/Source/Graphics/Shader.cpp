#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(std::string VertexPath, std::string FragmentPath)
{

	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(VertexPath);
		fShaderFile.open(FragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//------------------------------------------

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// shader Program
	ShaderID = glCreateProgram();
	glAttachShader(ShaderID, vertex);
	glAttachShader(ShaderID, fragment);
	glLinkProgram(ShaderID);
	// print linking errors if any
	glGetProgramiv(ShaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(ShaderID);
}

void Shader::Use() const
{
	glUseProgram(ShaderID);
}

void Shader::SetMatrix4x4(const std::string& name, glm::mat4 value) const
{
	auto location = glGetUniformLocation(ShaderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetInt(const std::string& name, int value) const
{
	auto location = glGetUniformLocation(ShaderID, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	auto location = glGetUniformLocation(ShaderID, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetMatrix4x4(int uniformID, glm::mat4 value) const
{
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetInt(int uniformID, int value) const
{
	glUniform1i(uniformID, value);
}

void Shader::SetFloat(int uniformID, float value) const
{
	glUniform1f(uniformID, value);

}
