#ifndef TEXTURE_H__
#define TEXTURE_H__

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

class Texture
{
	unsigned int texture;
public: 
	Texture(); 
	void LoadTexture(std::string path);
	void activeTexture();
};

#endif
