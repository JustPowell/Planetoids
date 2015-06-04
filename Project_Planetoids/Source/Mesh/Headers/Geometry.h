#pragma once
#include "../../Headers/Planetoids.h"

class Vertex;
class Edge;
class Face;

typedef vector<Vertex*> vertex_l;
typedef vector<Edge*> edge_l;
typedef vector<Face*> face_l;

class Geom
{
public:
	Geom();
	~Geom();

	template <typename T>
	void addAdj(T object);
	
	vertex_l getAdjVerts();
	edge_l	 getAdjEdges();
	face_l	 getAdjFaces();

private:
	vertex_l adj_v;
	edge_l	 adj_e;
	face_l	 adj_f;
};

class Vertex : Geom
{
public:
	Vertex();
	Vertex(vector3f loc);
	Vertex(vector3f loc, normal3f nor, color3f col);
	~Vertex();

	void setLocation(vector3f loc);
	void setNormal(normal3f nor);
	void setColor(color3f col);

	vector3f getLocation() const;
	normal3f getNormal() const;
	color3f getColor() const;

private:
	vector3f loc;
	normal3f nor;
	color3f col;
};

class Edge : Geom
{
public:
	Edge(Vertex* v0, Vertex* v1);
	~Edge();

	Vertex* getVert(int v);
	Vertex* getOther(int v);
	vector3f getCentroid() const;

private:
	Vertex *v0, *v1;
};

class Face : Geom
{
public:
	Face(Vertex* v0, Vertex* v1, Vertex* v2, Vertex* v3);
	~Face();

	void	 setVertices(Vertex* v0, Vertex* v1, Vertex* v2, Vertex* v3);
	vertex_l getVertices();
	vector3f getCentroid();
	color3f  getColor() const;

private:
	vertex_l vertexList;
	edge_l	 edgeList;
	color3f  color;
};

inline vector3f getCentroid(const Vertex* v0, const Vertex* v1) //TEMPORARY FUNCTION
{
	vector3f centroid;
	get<0>(centroid) = (get<0>(v0->getLocation()) + get<0>(v1->getLocation())) / 2;
	get<1>(centroid) = (get<1>(v0->getLocation()) + get<1>(v1->getLocation())) / 2;
	get<2>(centroid) = (get<2>(v0->getLocation()) + get<2>(v1->getLocation())) / 2;
	return centroid;
}