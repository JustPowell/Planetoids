#pragma once
#include "../Headers/Planetoids.h"

class Camera
{
public:
	Camera();
	Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);
	~Camera();

	glm::vec3 getPos();
	glm::vec3 getTarget();
	glm::vec3 getUp();

	void setViewMatrix(const glm::mat4& viewMatrix);
	glm::mat4 getViewMatrix();

	void update();
private:
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 viewMatrix;
};

