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

	vector<GLfloat> getLocations(); // Used for drawing
	vector<GLubyte> getIndices();	 // Used for drawing
	int getNumInd();

	typedef unordered_map<Vertex*, int> v_map;
	typedef unordered_map<Edge*, int>   e_map;
	typedef unordered_map<Face*, int>   f_map;
private:
	int num_v, num_e, num_f, num_i;

	vertex_l l_vertices;
	edge_l   l_edges;
	face_l   l_faces;

	v_map m_vertices;
	e_map m_edges;
	f_map m_faces;

	vector<GLfloat> l_vLocations;
	vector<GLubyte> l_indices;

	void storeVertLocation(Vertex* v);
	void storeIndex(Face* f);
};

