#include "common.h"

GLfloat distance(Vertex *ver1, Vertex *ver2)
{
	GLfloat dist;
	tup3f v1 = ver1->getLocation();
	tup3f v2 = ver2->getLocation();

	dist = sqrt(pow((get<0>(v1) - get<0>(v2)), 2) + pow((get<1>(v1) - get<1>(v2)), 2) + pow((get<2>(v1) - get<2>(v2)), 2));

	return dist;
}