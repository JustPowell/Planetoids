#include "../Headers/Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::addV(Vertex* v)
{
	this->l_vertices.push_back(v);
	this->vertex_map.emplace(v, this->l_vertices.size() - 1);
}

void Mesh::addE(Edge* e)
{
	this->l_edges.push_back(e);
	this->edge_map.emplace(e, this->l_edges.size() - 1);
}

void Mesh::addF(Face* f)
{
	this->l_faces.push_back(f);
	this->face_map.emplace(f, this->l_faces.size() - 1);
	for (int i = 0; i < f->getVertices().size(); i++)
	{
		this->addV(f->getVertices()[i]);
		this->addE(new Edge(f->getVertices()[i], f->getVertices()[(i + 1) % 4]));
	}
}

vertex_l& Mesh::getVerts()
{
	return this->l_vertices;
}

edge_l& Mesh::getEdges()
{
	return this->l_edges;
}

face_l& Mesh::getFaces()
{
	return this->l_faces;
}