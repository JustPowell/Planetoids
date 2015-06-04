#pragma once
#include "../../Misc/Headers/common.h"
#include "Geometry.h"
#include <unordered_map>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void addV(Vertex* v);
	void addE(Edge* e);
	void addF(Face* f);

	vertex_l& getVerts();
	edge_l&	  getEdges();
	face_l&   getFaces();

	typedef unordered_map<Vertex*, int> v_map;
	typedef unordered_map<Edge*, int>   e_map;
	typedef unordered_map<Face*, int>   f_map;
private:
	vertex_l l_vertices;
	edge_l   l_edges;
	face_l   l_faces;

	v_map vertex_map;
	e_map edge_map;
	f_map face_map;
};

