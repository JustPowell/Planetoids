#pragma once
#include "../../Headers/Planetoids.h"
#include <unordered_map>

class Vertex;
class Edge;
class Face;

typedef vector<Vertex*> vertex_l;
typedef vector<Edge*> edge_l;
typedef vector<Face*> face_l;

class Vertex
{
public:
	Vertex();
	Vertex(vector3f loc);
	Vertex(vector3f loc, normal3f nor, color3f col);
	~Vertex();

	void setLocation(vector3f loc);
	void setNormal(normal3f nor);
	void setColor(color3f col);
	void addAdjEdge(Edge* e);
	void addAdjFace(Face* f);

	vector3f getLocation() const;
	normal3f getNormal() const;
	color3f  getColor() const;
	edge_l   getAdjEdges() const;
	face_l   getAdjFaces() const;

private:
	vector3f loc;
	normal3f nor;
	color3f col;

	edge_l adj_e;
	face_l adj_f;
};

class Edge
{
public:
	Edge(Vertex* v0, Vertex* v1);
	~Edge();

	void addAdjVertex(Vertex* v);
	void addAdjFace(Face* f);

	Vertex* getVert(int v);
	Vertex* getOther(int v);
	vector3f getCentroid() const;
	vertex_l getAdjVertices();
	face_l getAdjFaces();

private:
	Vertex *v0, *v1;

	vertex_l adj_v;
	face_l	 adj_f;
};

class Face
{
public:
	Face(Vertex* v0, Vertex* v1, Vertex* v2, Vertex* v3);
	~Face();

	void	 setVertices(Vertex* v0, Vertex* v1, Vertex* v2, Vertex* v3);
	void	 addEdge(Edge* e);
	vertex_l getVertices();
	edge_l   getEdges();
	vector3f getCentroid();
	color3f  getColor() const;

	void setNormal(glm::vec3& norm);
	normal3f getNormal();

private:
	vertex_l vertexList;
	edge_l	 edgeList;
	color3f  color;

	normal3f f_normal;

	
};

inline vector3f getCentroid(const Vertex* v0, const Vertex* v1) //TEMPORARY FUNCTION
{
	vector3f cent;
	cent.x = (v0->getLocation().x + v1->getLocation().x) / 2;
	cent.y = (v0->getLocation().y + v1->getLocation().y) / 2;
	cent.z = (v0->getLocation().z + v1->getLocation().z) / 2;
	return cent;
}