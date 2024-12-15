#ifndef CAMERA_H__
#define CAMERA_H__
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
protected: 
	glm::mat4 view;
	glm::vec3 camPos; 
	glm::vec3 up;
	glm::vec3 WorldUp;
	glm::vec3 camRight;
	glm::vec3 camUp;
	glm::vec3 camFront;
	glm::vec3 direction; 


	float pitch; 
	float yaw;
	float const sens = 0.1f; 
	float spd;

	// Additional parameter
	bool toggleFreemode;
	bool grounded; // Indicator to disable gravity, reset the fall acceleration and allow camera to jump if true. By default this will be enabled when camera hit the y <1 pos to avoid infinite falling.
	const float gravity = 9.1f; // Value by default of gravity, might be a tad much in this context
	float fallAcceleration; // Accumulation of acceleration of Camera being in the air. will be capped at a certain value so the camera will not be launched downward at an infinite amount of acceleration.
	float freeGravityTime;  // whenever i want to jump, gravity will not affect me for that variable time interval
	float jumpTime; // Time how long jump should launch me upward ( without this, it would be an instantaneous travel ) 



public:
	Camera(glm::vec3 _campos); 
	glm::mat4 getMatrice(); 

	void cameraMovement(glm::vec2 _input, float _dt);
	void setCamPos(glm::vec3 _pos);
	void lookAtSource(glm::vec3 _target);
	void Rotation(glm::vec2 _input); 
	void updateCam(); 

	void jump(); 

	void toggle(); 
	glm::vec3 getcamPos(); 
};

#endif
