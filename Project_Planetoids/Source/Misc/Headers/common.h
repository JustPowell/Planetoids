#pragma once

#include "../../Headers/Planetoids.h"
#include "../../Mesh/Headers/Geometry.h"
class Vertex;
/*
	Variables
*/
struct vertlist
{
	vertex_l vertices;
	int n;
};

/*
	Functions
*/
/*inline GLfloat distance(Vertex *ver1, Vertex *ver2)
{
	GLfloat dist;
	vector3f v1 = ver1->getLocation();
	vector3f v2 = ver2->getLocation();

	dist = sqrt(pow((get<0>(v1) -get<0>(v2)), 2) + pow((get<1>(v1) -get<1>(v2)), 2) + pow((get<2>(v1) -get<2>(v2)), 2));

	return dist;
}*/

inline Vertex* access3dArray(vertlist& vlist, int x, int y, int z)
{
	return vlist.vertices[x + vlist.n * (y + vlist.n * z)];
}

inline void putin3dArray(vertlist& vlist, Vertex *v, int x, int y, int z)
{
	vlist.vertices[x + vlist.n * (y + vlist.n * z)] = v;
}