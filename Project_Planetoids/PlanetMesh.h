#pragma once

//#include "Mesh.h"
#include "Vertex.h"
#include "Face.h"
#include "Quadtree.h"
#include <unordered_map>

class Face;
class Vertex;

class PlanetMesh
{
public:
	PlanetMesh(GLfloat radius, int sublvl);
	~PlanetMesh();

	struct side {
		Face::face_l faceList;
		side *top;
		side *bot;
		side *left;
		side *right;
	};

	side* getSide(int idx);
	Quadtree* getQuad(int idx);
	void subdivide(int lvl);

private:
	void initVertices();
	void addVert(Vertex *vert);
	void initCube();
	void toSphere();

	Vertex::vertex_l calcNewVerts(Face *face);

	struct key_hash : public unary_function<tup3f, size_t>
	{
		size_t operator()(const tup3f& k) const
		{
			return ((int)get<0>(k) ^ (int)get<1>(k) ^ (int)get<2>(k));
		}
	};

	struct key_equal : public binary_function<tup3f, tup3f, bool>
	{
		bool operator()(const tup3f& v0, const tup3f& v1) const
		{
			return (get<0>(v0) == get<0>(v1) && get<1>(v0) == get<1>(v1) && get<2>(v0) == get<2>(v1));
		}
	};

	typedef unordered_map<tup3f, Vertex*, key_hash, key_equal> vertexMap;

	Vertex::vertex_l initVerts;
	vertexMap vertexTable;
	vector<side*> cubeside;
	vector<Quadtree*> quadtrees;
	GLfloat radius;
};