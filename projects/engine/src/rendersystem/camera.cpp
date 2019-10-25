#include "camera.h"
#include <glm/gtx/transform.hpp>

Camera::Camera()
{
	this->viewDirection = glm::vec3(0.0f,0.0f,-1.0f);
	this->UP = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition-(this->oldMousePosition);
	this->viewDirection = glm::mat3(glm::rotate(mouseDelta.x, this->UP)) * this->viewDirection;


	this->oldMousePosition = newMousePosition;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(this->position, this->position + this->viewDirection, this->UP);
}
