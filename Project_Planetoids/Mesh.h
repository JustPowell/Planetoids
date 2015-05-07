#pragma once

#include "Planetoids.h"
#include "Face.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

private:
	vector<Vertex*> vertexList;
	vector<Face*> faceList;
};

