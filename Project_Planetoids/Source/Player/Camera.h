#pragma once
#include "../Headers/Planetoids.h"
#define al 16

#if !_DEBUG
__declspec(align(al)) class Camera
#else
class Camera
#endif
{
public:
	Camera();
	Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);
	~Camera();

	void init(const glm::vec3& pos, const glm::vec3& tar, const glm::vec3& up);
	void update();
	void setPos(const glm::vec3& pos);
	void setTarget(const glm::vec3& tar);
	void setUp(const glm::vec3& up);

#if !_DEBUG
	void* operator new(size_t i);
	void operator delete(void *p);
#endif

	glm::vec3 getPos();
	glm::vec3 getTarget();
	glm::vec3 getUp();

	void setViewMatrix(const glm::mat4& viewMatrix);
	glm::mat4 getViewMatrix();

	void move(int key, int action, int mods);
	void move(GLFWwindow* window, double xpos, double ypos);
	float getSpeed();
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
	float speed = 2.005f;
	float mousespeed = .00005f;
};

