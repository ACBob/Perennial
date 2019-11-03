#include "camera.h"
#include <glm/gtx/transform.hpp>

#define UP_VEC glm::vec3(0.0f, 0.0f, 1.0f)

Camera::Camera(glm::vec3 position, glm::vec3 target)
{
	this->position = position;
    this->target = target;
    this->direction = glm::normalize(position - target);
    this->right = glm::normalize(glm::cross(UP_VEC, this->direction));
    this->up = glm::cross(this->direction, this->right);
    
    this->view = glm::lookAt(this->position,
                             this->target,
                             UP_VEC);
    
    

}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition-(this->oldMousePosition);
	this->view = glm::lookAt(this->position,
                             this->target,
                             UP_VEC);
}

