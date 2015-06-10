#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
{
	this->pos = pos;
	this->target = target;
	this->up = up;

	this->viewMatrix = glm::lookAt(pos, target, up);
}


Camera::~Camera()
{
}

glm::vec3 Camera::getPos()
{
	return this->pos;
}

glm::vec3 Camera::getTarget()
{
	return this->target;
}

glm::vec3 Camera::getUp()
{
	return this->up;
}

void Camera::setViewMatrix(const glm::mat4& viewMatrix)
{
	this->viewMatrix = viewMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

void Camera::update()
{

}