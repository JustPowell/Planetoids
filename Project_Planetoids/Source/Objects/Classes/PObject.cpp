#include "../Headers/PObject.h"


PObject::PObject()
{
}


PObject::~PObject()
{
}

void PObject::update()
{

}

void PObject::draw()
{

}

void PObject::setLoc(glm::vec3 loc)
{
	this->loc = loc;
}

glm::vec3 PObject::getLoc()
{
	return this->loc;
}

void PObject::setModelMatrix(const glm::mat4& modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

glm::mat4 PObject::getModelMatrix()
{
	return this->modelMatrix;
}