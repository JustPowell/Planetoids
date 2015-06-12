#include "../Headers/Geometry.h"

//Vertex Class
Vertex::Vertex()
{
}

Vertex::Vertex(vector3f loc)
{
	this->loc = loc;
	this->nor = glm::vec3(0.f, 0.f, 0.f);
	this->col = glm::vec3((float)(rand() % 255) / 255, (float)(rand() % 255) / 255, (float)(rand() % 255) / 255);
	//get<0>(this->col) = (float)(rand() % 255) / 255;
	//get<1>(this->col) = (float)(rand() % 255) / 255;
	//get<2>(this->col) = (float)(rand() % 255) / 255;
}

Vertex::Vertex(vector3f loc, normal3f nor, color3f col)
{
	this->loc = loc;
	this->nor = nor;
	this->col = col;
}

Vertex::~Vertex()
{
}

void Vertex::setLocation(vector3f loc)
{
	this->loc = loc;
}

void Vertex::setNormal(normal3f nor)
{
	this->nor = nor;
}

void Vertex::setColor(color3f col)
{
	this->col = col;
}

void Vertex::addAdjEdge(Edge* e)
{
	this->adj_e.push_back(e);
}

void Vertex::addAdjFace(Face* f)
{
	this->adj_f.push_back(f);
}

vector3f Vertex::getLocation() const
{
	return this->loc;
}

normal3f Vertex::getNormal() const
{
	return this->nor;
}

color3f Vertex::getColor() const
{
	return this->col;
}

edge_l Vertex::getAdjEdges() const
{
	return this->adj_e;
}

face_l Vertex::getAdjFaces() const
{
	return this->adj_f;
}

//Edge Class
Edge::Edge(Vertex* v0, Vertex* v1)
{
	this->v0 = v0;
	this->v1 = v1;
	this->addAdjVertex(v0);
	this->addAdjVertex(v1);
	v0->addAdjEdge(this);
	v1->addAdjEdge(this);
}

Edge::~Edge()
{
}

void Edge::addAdjVertex(Vertex* v)
{
	this->adj_v.push_back(v);
}

void Edge::addAdjFace(Face* f)
{
	this->adj_f.push_back(f);
}

/*
	Return the specified Vertex
*/
Vertex* Edge::getVert(int v)
{
	switch (v)
	{
	case 0:
		return this->v0;
	case 1:
		return this->v1;
	}
}

/*
	Return the opposite vertex of the edge.
	Ex. getOther(v0) = v1
*/
Vertex* Edge::getOther(int v)
{
	switch (v)
	{
	case 0:
		return this->v1;
	case 1:
		return this->v0;
	}
}

vector3f Edge::getCentroid() const
{
	vector3f cent;
	cent.x = (v0->getLocation().x + v1->getLocation().x) / 2;
	cent.y = (v0->getLocation().y + v1->getLocation().y) / 2;
	cent.z = (v0->getLocation().z + v1->getLocation().z) / 2;
	return cent;
}

vertex_l Edge::getAdjVertices()
{
	return this->adj_v;
}

face_l Edge::getAdjFaces()
{
	return this->adj_f;
}

//Face Class
Face::Face(Vertex* v0, Vertex* v1, Vertex* v2, Vertex* v3)
{
	this->setVertices(v0, v1, v2, v3);
	//get<0>(this->color) = (float)(rand() % 255) / 255;
	//get<1>(this->color) = (float)(rand() % 255) / 255;
	//get<2>(this->color) = (float)(rand() % 255) / 255;
}

Face::~Face()
{
}

void Face::setVertices(Vertex* v0, Vertex* v1, Vertex* v2, Vertex* v3)
{
	this->vertexList.push_back(v0);
	this->vertexList.push_back(v1);
	this->vertexList.push_back(v2);
	this->vertexList.push_back(v3);
	v0->addAdjFace(this);
	v1->addAdjFace(this);
	v2->addAdjFace(this);
	v3->addAdjFace(this);
}

void Face::addEdge(Edge* e)
{
	edgeList.push_back(e);
	e->addAdjFace(this);
}

vertex_l Face::getVertices()
{
	return this->vertexList;
}

edge_l Face::getEdges()
{
	return this->edgeList;
}

color3f Face::getColor() const
{
	return this->color;
}

void Face::setNormal(glm::vec3& norm)
{
	this->f_normal = norm;
}

normal3f Face::getNormal()
{
	return this->f_normal;
}