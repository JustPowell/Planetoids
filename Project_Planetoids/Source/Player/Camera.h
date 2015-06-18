#pragma once
#include "../Headers/Planetoids.h"

class Camera
{
public:
	Camera();
	Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);
	~Camera();

	void update();
	glm::vec3 getPos();
	glm::vec3 getTarget();
	glm::vec3 getUp();

	void setViewMatrix(const glm::mat4& viewMatrix);
	glm::mat4 getViewMatrix();

	void move(int key, int action);
	void move(GLFWwindow* window, double xpos, double ypos);
private:
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 viewMatrix;
	GLfloat xpos, ypos;
	float hangle = 3.14f;
	float vangle = 0.f;
	float initFov = 45.f;
	float speed = 5.f;
	float mousespeed = .005f;
};

