#pragma once
#include "../Headers/Planetoids.h"

class Camera
{
public:
	Camera();
	Camera(vector3f& pos, vector3f& target, vector3f& up);
	~Camera();

	vector3f& getPos();
	vector3f& getTarget();
	vector3f& getUp();

private:
	vector3f pos;
	vector3f target;
	vector3f up;
};

