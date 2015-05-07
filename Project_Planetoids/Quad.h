#pragma once

class Vertex;
class Face;

#include "Vertex.h"
#include "Face.h"

class Quad
{
public:
	Quad(Face *face);
	~Quad();

	void addParent(Quad *parent);
	void addNode(int idx, Face *face);
	Quad* getNode(int idx);
	void setVert(int idx, Vertex *vert);
	vector<Vertex *> getVerts();

private:
	Quad *parent;
	Quad *node[4];

	vector<Vertex *> vert;
};

