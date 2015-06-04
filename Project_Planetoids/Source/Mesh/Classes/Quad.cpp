#include "../Headers/Quad.h"

Quad::Quad(Face *face)
{
	this->parent = NULL;

	for (int i = 0; i < 4; i++)
	{
		this->node[i] = NULL;
	}
	this->vert.push_back(face->getVertices()[0]);
	this->vert.push_back(face->getVertices()[1]);
	this->vert.push_back(face->getVertices()[2]);
	this->vert.push_back(face->getVertices()[3]);
}

Quad::~Quad()
{
}

void Quad::addParent(Quad *parent)
{
	this->parent = parent;
}

void Quad::addNode(int idx, Face *face)
{
	this->node[idx] = new Quad(face);
	this->node[idx]->addParent(this);
}

Quad* Quad::getNode(int idx)
{
	return this->node[idx];
}

void Quad::setVert(int idx, Vertex *vert)
{
	this->vert[idx] = vert;
}

vector<Vertex *> Quad::getVerts()
{
	return this->vert;
}