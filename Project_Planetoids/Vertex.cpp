#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(tup3f loc)
{
	this->loc = loc;
	get<0>(this->col) = (float)(rand() % 255) / 255;
	get<1>(this->col) = (float)(rand() % 255) / 255;
	get<2>(this->col) = (float)(rand() % 255) / 255;
}

Vertex::Vertex(tup3f loc, tup3f nor, tup3f col)
{
	this->loc = loc;
	this->nor = nor;
	this->col = col;
}

Vertex::~Vertex()
{
}

void Vertex::setLocation(tup3f loc)
{
	this->loc = loc;
}

void Vertex::setNormal(tup3f nor)
{
	this->nor = nor;
}

void Vertex::setColor(tup3f col)
{
	this->col = col;
}

tup3f Vertex::getLocation()
{
	return this->loc;
}

tup3f Vertex::getNormal()
{
	return this->nor;
}

tup3f Vertex::getColor()
{
	return this->col;
}

tup3f Vertex::getCentroid(Vertex *v1)
{
	tup3f centroid;
	get<0>(centroid) = (get<0>(this->getLocation()) + get<0>(v1->getLocation())) / 2;
	get<1>(centroid) = (get<1>(this->getLocation()) + get<1>(v1->getLocation())) / 2;
	get<2>(centroid) = (get<2>(this->getLocation()) + get<2>(v1->getLocation())) / 2;
	return centroid;
}

tup3f Vertex::getCentroid(Vertex *v1, Vertex *v2, Vertex *v3)
{
	tup3f centroid;
	get<0>(centroid) = (get<0>(this->getLocation()) + get<0>(v1->getLocation()) + get<0>(v2->getLocation()) + get<0>(v3->getLocation())) / 4;
	get<1>(centroid) = (get<1>(this->getLocation()) + get<1>(v1->getLocation()) + get<1>(v2->getLocation()) + get<1>(v3->getLocation())) / 4;
	get<2>(centroid) = (get<2>(this->getLocation()) + get<2>(v1->getLocation()) + get<2>(v2->getLocation()) + get<2>(v3->getLocation())) / 4;
	return centroid;
}