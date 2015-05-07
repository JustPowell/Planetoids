#pragma once
#include "Planetoids.h"

class Vertex
{
public:
	Vertex();
	Vertex(tup3f loc);
	Vertex(tup3f loc, tup3f nor, tup3f col);
	~Vertex();

	void setLocation(tup3f loc);
	void setNormal(tup3f nor);
	void setColor(tup3f col);

	tup3f getLocation();
	tup3f getNormal();
	tup3f getColor();

	tup3f getCentroid(Vertex *v1);
	tup3f getCentroid(Vertex *v1, Vertex *v2, Vertex *v3);

	typedef vector<Vertex*> vertex_l;

private:
	tup3f loc;
	tup3f nor;
	tup3f col;
};

