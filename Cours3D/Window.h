#ifndef WINDOW_H__
#define WINDOW_H__
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"

class Window
{
	GLFWwindow* window; 
	static Shader* shader; 
	static Camera* camera; 
	static glm::vec2* input;
	static glm::vec2* mouseinput;
	static glm::vec2* lastMousePos; 

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
	float time;
	float angle;

	int width, height; 

public:
	Window(); 
	void init(); 
	void create(int _width, int _height, std::string titre);
	bool isOpen();
	void clear(float _r, float _g, float _b);
	void pollEvents(); 
	void setShader(Shader* _shader); 
	void setCamera(Camera* _camera);
	GLFWwindow* getWindow(); 
	void setModelMatrix4(glm::mat4 _model);
	void setDeltaTime(float _time);

	glm::mat4 getprojection();
	glm::mat4 getview(); 
	glm::mat4 getmodel(); 


	void process(); 


	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void close(); 
};

#endif

