#include "Camera.h"

/*
	Camera controls thanks to: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
*/

Camera::Camera()
{
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
{
	this->pos = pos;
	this->xpos = 1024.f/2.f;
	this->ypos = 768.f/2.f;
	this->viewMatrix = glm::lookAt(pos, target, up);
	this->target = glm::vec3(cosf(vangle)*sinf(hangle), sinf(vangle), cos(vangle) * cos(hangle));
}


Camera::~Camera()
{
}

void Camera::update()
{
	this->target = glm::vec3(cosf(vangle)*sinf(hangle), sinf(vangle), cos(vangle) * cos(hangle));
	this->right = glm::vec3(sin(hangle - 3.14f / 2.f), 0, cos(hangle - 3.14f / 2.f));
	this->up = glm::normalize(glm::cross(right, this->target));
	this->viewMatrix = glm::lookAt(this->pos, this->pos - this->target, this->up);
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

void Camera::move(int key, int action)
{

	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->pos -= this->target * speed;
	}
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->pos += this->target * speed;
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->pos -= right * speed;
	}
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->pos += right * speed;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{		
		this->hangle += .1f;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->hangle -= .1f;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->vangle += .1f;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->vangle -= .1f;
	}
}

//TODO: need to fix this up.
void Camera::move(GLFWwindow* window, double xpos, double ypos)
{
	if (xpos > 1024.f)
		xpos = 1024.f;
	if (xpos < 0.f)
		xpos = 0.f;
	if (ypos > 768.f)
		ypos = 768.f;
	if (ypos < 0.f)
		ypos = 0.f;

	this->hangle += mousespeed * float(this->xpos - xpos);
	this->vangle += mousespeed * float(this->ypos - ypos);
	if (vangle > 90.f)
		vangle = 90.f;
	else if (vangle > -90.f)
		vangle = -90.f;
}