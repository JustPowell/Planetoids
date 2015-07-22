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
	PlanetMesh();
	PlanetMesh(GLfloat radius, int sublvl, int random = 0, int atmo = 0);
	~PlanetMesh();

	void setRadius(GLfloat radius);
	void setSubdivisionLvl(int sublvl);
	void buildPlanet(int atmo);

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
	int sublvl;
	int random;
	vector<side*> cubeside;
	GLfloat radius;

	vertex_l calcNewVerts(unordered_map<Edge*, Vertex*>& newVerts, Face *face);
	void initVertices(int sublvl);
	void initCube(int atmo);
	void initAtmoCube();
	void toSphere();

	void addFace();
};