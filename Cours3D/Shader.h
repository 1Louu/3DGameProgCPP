#ifndef SHADER_H__
#define SHADER_H__
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public: 
	unsigned int ID;
	unsigned int vertexShader; 
	unsigned int fragmentShader; 

	Shader(const char* vertexPath, const char* fragmentPath); 

	void Process(std::string vertexCode, std::string fragmentCode); // == set up des shaders

	void Use() const; // use program ==  render part 
	void Shutdown() const; 

	void SetInt(const std::string& name, int value) const; 

	void SetMatrix4(const std::string& name, const glm::mat4& value)const; 
	void SetVector3(const std::string& name, float x, float y, float z) const; 
	void SetVector3(const std::string& name, const glm::vec3& value) const; 
	void SetFloat(const std::string& name, float value) const; 

private: 
	std::string GetFileContent(const char* path);
};

#endif

