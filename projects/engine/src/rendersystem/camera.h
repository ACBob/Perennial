#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H
#include <glm/glm.hpp>

class Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;

public:
	Camera();
	glm::mat4 getWorldToViewMatrix() const;
	void mouseUpdate(const glm::vec2& newMousePosition);



#endif
