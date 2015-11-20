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
	void addEdges(Face* f);

	vertex_l& getVerts();

	edge_l&	  getEdges();
	face_l&   getFaces();

	vector<GLfloat> getLocations(); // Used for drawing
	vector<GLuint> getIndices();	 // Used for drawing
	vector<GLfloat> getNormals();
	vector<GLfloat> getColors();

	int getNumInd();

	typedef unordered_map<Vertex*, int> v_map;
	typedef unordered_map<Face*, int>   f_map;

	struct key_hash : public unary_function<Edge, size_t>{
		size_t operator()(Edge* k) const{
			return ((int)k->getVert(0) ^ (int)k->getVert(1));
		}
	};

	struct key_equal : public binary_function<Edge, Edge, bool>{
		bool operator()(Edge* e0, Edge* e1) const{
			return ((e0->getVert(0) == e1->getVert(0) && e0->getVert(1) == e1->getVert(1))
				 || (e0->getVert(0) == e1->getVert(1) && e0->getVert(1) == e1->getVert(0)));
		}
	};
	typedef unordered_map<Edge*, int, key_hash, key_equal> e_map;

protected:
	int num_v, num_e, num_f, num_i;
	vertex_l l_vertices;
	edge_l   l_edges;
	face_l   l_faces;

	v_map m_vertices;
	e_map m_edges;
	f_map m_faces;

	void updateLocations();
	void updateIndex();
	void updateColors();
	void updateNormals();
	void calcNormals();
	void calcFaceNormal(Face* f);

private:
	vector<GLfloat> l_vLocations;
	vector<GLuint> l_indices;
	vector<GLfloat> l_normals;
	vector<GLfloat> l_colors;

	void storeVertLocation(Vertex* v);
	void storeIndex(Face* f);
	void storeNormals(Vertex* v);
	void storeColor(Vertex* v);

	Edge* checkEdge(Edge* e);
};

