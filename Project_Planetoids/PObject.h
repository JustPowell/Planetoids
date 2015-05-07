#pragma once
#include "Planetoids.h"
#include "Vertex.h"

class PObject
{
public:
	PObject();
	PObject(string name, int id);
	~PObject();

	void setName(string name);
	void setId(int id);
	void setVertices(vector<Vertex> vertices);
	void setNormals();
	void setColors();
	void setIndices(GLubyte *indices);
	void subdivide(int lvl);
	void update();

	string		getName();
	int			getId();
	GLfloat*	getVertices();
	GLfloat*	getNormals();
	GLfloat*	getColors();
	GLubyte*	getIndices();

private:
	string name;
	int id;
	vector<Vertex> vertexList;
	GLfloat *vertices;
	GLfloat *normals;
	GLfloat *colors;
	GLubyte *indices;
};