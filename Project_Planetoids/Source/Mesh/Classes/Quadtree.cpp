#include "../Headers/Quadtree.h"

Quadtree::Quadtree(Face *face)
{
	this->init(face);
}

Quadtree::~Quadtree()
{
	delete root;
}

void Quadtree::init(Face *face)
{
	this->root = new Quad(face);
}

Quad* Quadtree::getRoot()
{
	return this->root;
}

vector<Quad*> Quadtree::getQuadlist(int sublvl)
{
	vector<Quad*> quadlist;
	this->traverse(this->root, &quadlist, sublvl, 0);
	return quadlist;
}

void Quadtree::traverse(Quad *quad, vector<Quad*> *quadlist, int sublvl, int curlvl)
{
	if (curlvl < sublvl)
	{
		this->traverse(quad->getNode(0), quadlist, sublvl, curlvl++);
		this->traverse(quad->getNode(1), quadlist, sublvl, curlvl++);
		this->traverse(quad->getNode(2), quadlist, sublvl, curlvl++);
		this->traverse(quad->getNode(3), quadlist, sublvl, curlvl++);
	}
	else
	{
		quadlist->push_back(quad);
	}
}

int Quadtree::getDepth()
{
	Quad *quad = this->root;
	int depth = 0;

	while (quad != NULL)
	{
		quad = quad->getNode(0);
		depth++;
	}
	return depth;
}