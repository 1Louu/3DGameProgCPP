#include "Camera.h"

Camera::Camera(glm::vec3 _campos)
{
    camPos = _campos; 
    up = glm::vec3(0.0f, -1.0f, 0.0f); 
    WorldUp= up; 
    camFront = glm::vec3(0.0f, 0.0f, 1.0f);
    direction = glm::vec3(0, 0, 0);
    camRight = glm::normalize(glm::cross(WorldUp, camFront));
    camUp = glm::cross(camFront, camRight);
    pitch = 0.f;
    yaw= -90.0f;
    spd = 2.25;
    toggleFreemode = false; 
    updateCam();
}

glm::mat4 Camera::getMatrice()
{
    return glm::lookAt(camPos, camPos + camFront, up);
}

void Camera::cameraMovement(glm::vec2 _input,float _dt)
{
    if (toggleFreemode) {
        ////Free mode
        if (_input.x != 0) {
            camPos += -_input.x * camRight * _dt * spd;
        }
        if (_input.y != 0) {
            camPos += _input.y * camFront * _dt * spd;
        }
    }else{

        //Real movement 
        if (_input.x != 0) {
            camPos += -_input.x * camRight * _dt * spd;
        }
        if (_input.y != 0) {
            camPos += _input.y * glm::cross(camRight, camUp) * _dt * spd;
        }
    }
    if (grounded) { // If player is grounded 
    }
    else {
        if (!toggleFreemode){
            if (jumpTime > 0) { // If jump was pressed 
                camPos.y += _dt * 10; // 10 is the speed of the jump. I know its bit high but shh
                fallAcceleration = 0;
                jumpTime -= _dt;
            }
            else { // if jump time was over then we procceed to enabling gravity
                fallAcceleration += _dt;
                if (fallAcceleration > 2) { // capping the fallacceleration
                    fallAcceleration = 2;
                }
                camPos.y += -gravity * _dt * fallAcceleration; // meaning over 2 seconds, we reach the highest fall velocity. For more realistic fall speed, i'd need to do some exponential math but eh.
            }
        }
    }

    if (camPos.y < 1 && !toggleFreemode) { // Measure to prevent player being under the map 
        camPos.y = 1; 
        grounded = true; 
        jumpTime = 0; 
        fallAcceleration = 0; 
    }
}

void Camera::setCamPos(glm::vec3 _pos)
{
    camPos = _pos; 
}

void Camera::lookAtSource(glm::vec3 _target)
{
    view = glm::lookAt(camPos,_target,up);
}

void Camera::Rotation(glm::vec2 _input)
{
    yaw -= -_input.x * sens; 
    pitch -= -_input.y * sens; 
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCam();

}

void Camera::updateCam()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(direction);
    camRight = glm::normalize(glm::cross(WorldUp, camFront));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(camRight, camFront));
}

void Camera::jump()
{
    if (grounded && !toggleFreemode) {
        jumpTime = 0.75; 
        grounded = false; 
    }
}

void Camera::toggle()
{
    if (toggleFreemode) {
        toggleFreemode = false;
    }
    else {
        toggleFreemode = true;
        grounded = false;
        jumpTime = 0;
    }
}

glm::vec3 Camera::getcamPos()
{
    return camPos;
}
;
