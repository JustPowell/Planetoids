#pragma once

class Quad;
class Face;

#include "../../Headers/Planetoids.h"
#include "Quad.h"
#include "Geometry.h"


class Quadtree
{
public:
	Quadtree(Face *face);
	~Quadtree();

	void init(Face *face);
	Quad* getRoot();

	vector<Quad*> getQuadlist(int sublvl);
	int getDepth();

private:
	Quad *root;

	void traverse(Quad *quad, vector<Quad*> *quadlist, int sublvl, int curlvl);
};

