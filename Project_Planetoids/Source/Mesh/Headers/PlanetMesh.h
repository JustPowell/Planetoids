#pragma once

#include "Geometry.h"
#include "Mesh.h"
#include "../../Misc/Headers/common.h"
#include <unordered_map>

class Face;
class Vertex;

class PlanetMesh : public Mesh
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
	void subdivide(int lvl);

private:
	vector<side*> cubeside;
	GLfloat radius;

	vertex_l calcNewVerts(Face *face);
	void initVertices(int sublvl);
	void addVert(Vertex *vert);
	void initCube();
	void toSphere();

	void addFace();
};