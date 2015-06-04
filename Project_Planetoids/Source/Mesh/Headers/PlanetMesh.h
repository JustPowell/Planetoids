#pragma once

#include "Geometry.h"
#include "Mesh.h"
//#include "Quadtree.h"
#include "../../Misc/Headers/common.h"
#include <unordered_map>

class Face;
class Vertex;

class PlanetMesh : Mesh
{
public:
	PlanetMesh(GLfloat radius, int sublvl);
	~PlanetMesh();

	struct side {
		face_l faceList;
		side *top;
		side *bot;
		side *left;
		side *right;
	};

	side* getSide(int idx);
	//Quadtree* getQuad(int idx);
	void subdivide(int lvl);

private:
	vertex_l initVerts;
	
	vector<side*> cubeside;
	//vector<Quadtree*> quadtrees;
	GLfloat radius;

	vertex_l calcNewVerts(Face *face);

	struct key_hash : public unary_function<Edge, size_t>
	{
		size_t operator()(Edge* k) const
		{
			return ((int)k->getVert(0) ^ (int)k->getVert(1));
		}
	};

	struct key_equal : public binary_function<Edge, Edge, bool>
	{
		bool operator()(Edge* e0, Edge* e1) const
		{
			return ((int)e0->getVert(0) == (int)e1->getVert(0) && (int)e0->getVert(1) == (int)e1->getVert(1));
		}
	};

	typedef unordered_map<vector3f, Vertex*, key_hash, key_equal> vertexMap;
	vertexMap vertexTable;


	void initVertices(int sublvl);
	void addVert(Vertex *vert);
	void initCube();
	void toSphere();

	void addFace();
};