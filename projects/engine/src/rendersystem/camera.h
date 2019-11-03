#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H
#include <glm/glm.hpp>

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 direction;    
    glm::vec3 up;
    glm::vec3 right;

    glm::mat4 view;

    glm::vec2 oldMousePosition;
    

public:
	Camera(glm::vec3 position, glm::vec3 target);
	glm::mat4 getWorldToViewMatrix() const;
	void mouseUpdate(const glm::vec2& newMousePosition);
};


#endif
