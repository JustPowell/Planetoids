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

inline Vertex* access3dArray(vertlist& vlist, int x, int y, int z)
{
	return vlist.vertices[x + vlist.n * (y + vlist.n * z)];
}

inline void putin3dArray(vertlist& vlist, Vertex *v, int x, int y, int z)
{
	vlist.vertices[x + vlist.n * (y + vlist.n * z)] = v;
}

template<typename T>
inline void clearVector(T vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		delete vec[i];
	}
}