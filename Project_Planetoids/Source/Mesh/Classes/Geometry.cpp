#include "../Headers/Geometry.h"

//Geometry class. Contains adjacency information.
Geom::Geom()
{
}

Geom::~Geom()
{
}

//TODO: Add checking to make sure the object has not already been added to the list of adj objects.
template <typename T>
void Geom::addAdj(T object)
{
	if (typeid(object).name() == typeid(Vertex).name())
	{
		this->adj_v.push_back(object);
	}
	else if (typeid(object).name() == typeid(Edge).name())
	{
		this->adj_e.push_back(object);
	}
	else if (typeid(object).name() == typeid(Face).name())
	{
		this->adj_f.push_back(object);
	}
	object->addAdj(this); //WILL CAUSE AN INFINITE LOOP AT THE MOMENT. 
}

vertex_l Geom::getAdjVerts()
{
	return this->adj_v;
}

edge_l Geom::getAdjEdges()
{
	return this->adj_e;
}

face_l Geom::getAdjFaces()
{
	return this->adj_f;
}

//Vertex Class
Vertex::Vertex()
{
}

Vertex::Vertex(vector3f loc)
{
	this->loc = loc;
	get<0>(this->col) = (float)(rand() % 255) / 255;
	get<1>(this->col) = (float)(rand() % 255) / 255;
	get<2>(this->col) = (float)(rand() % 255) / 255;
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

//Edge Class
Edge::Edge(Vertex* v0, Vertex* v1)
{
	this->v0 = v0;
	this->v1 = v1;
	//this->addAdj(v0); //Need to add checkin in adj before use.
	//this->addAdj(v1);
}

Edge::~Edge()
{
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
	vector3f centroid;
	get<0>(centroid) = (get<0>(v0->getLocation()) + get<0>(v1->getLocation())) / 2;
	get<1>(centroid) = (get<1>(v0->getLocation()) + get<1>(v1->getLocation())) / 2;
	get<2>(centroid) = (get<2>(v0->getLocation()) + get<2>(v1->getLocation())) / 2;
	return centroid;
}

//Face Class
Face::Face(Vertex* v0, Vertex* v1, Vertex* v2, Vertex* v3)
{
	this->setVertices(v0, v1, v2, v3);
	get<0>(this->color) = (float)(rand() % 255) / 255;
	get<1>(this->color) = (float)(rand() % 255) / 255;
	get<2>(this->color) = (float)(rand() % 255) / 255;
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
}

vertex_l Face::getVertices()
{
	return this->vertexList;
}

color3f Face::getColor() const
{
	return this->color;
}

vector3f Face::getCentroid()
{
	vector3f centroid;
	get<0>(centroid) = (get<0>(vertexList[0]->getLocation()) + get<0>(vertexList[1]->getLocation()) + get<0>(vertexList[2]->getLocation()) + get<0>(vertexList[3]->getLocation())) / 4;
	get<1>(centroid) = (get<1>(vertexList[0]->getLocation()) + get<1>(vertexList[1]->getLocation()) + get<1>(vertexList[2]->getLocation()) + get<1>(vertexList[3]->getLocation())) / 4;
	get<2>(centroid) = (get<2>(vertexList[0]->getLocation()) + get<2>(vertexList[1]->getLocation()) + get<2>(vertexList[2]->getLocation()) + get<2>(vertexList[3]->getLocation())) / 4;
	return centroid;
}