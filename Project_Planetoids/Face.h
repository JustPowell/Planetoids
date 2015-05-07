#pragma once

#include "Planetoids.h"
#include "Vertex.h"

class Vertex;

class Face
{
public:
	Face(Vertex *v0, Vertex *v1, Vertex *v2, Vertex *v3);
	~Face();

	void			setVertices(Vertex *v0, Vertex *v1, Vertex *v2, Vertex *v3);
	vector<Vertex*> getVertices();

	typedef vector<Face*> face_l;
	tup3f getColor();

private:
	Vertex::vertex_l vertexList;
	tup3f color;
};

