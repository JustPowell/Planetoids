#include "Face.h"

Face::Face(Vertex *v0, Vertex *v1, Vertex *v2, Vertex *v3)
{
	this->setVertices(v0, v1, v2, v3);
	get<0>(this->color) = (float)(rand() % 255) / 255;
	get<1>(this->color) = (float)(rand() % 255) / 255;
	get<2>(this->color) = (float)(rand() % 255) / 255;
}

Face::~Face()
{
}

void Face::setVertices(Vertex *v0, Vertex *v1, Vertex *v2, Vertex *v3)
{
	this->vertexList.push_back(v0);
	this->vertexList.push_back(v1);
	this->vertexList.push_back(v2);
	this->vertexList.push_back(v3);
}

vector<Vertex*> Face::getVertices()
{
	return this->vertexList;
}

tup3f Face::getColor()
{
	return this->color;
}