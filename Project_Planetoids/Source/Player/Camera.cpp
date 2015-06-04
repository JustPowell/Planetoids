#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(vector3f& pos, vector3f& target, vector3f& up)
{
	this->pos = pos;
	this->target = target;
	this->up = up;
}


Camera::~Camera()
{
}

vector3f& Camera::getPos()
{
	return this->pos;
}

vector3f& Camera::getTarget()
{
	return this->target;
}

vector3f& Camera::getUp()
{
	return this->up;
}