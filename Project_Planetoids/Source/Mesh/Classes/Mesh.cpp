#include "../Headers/Mesh.h"


Mesh::Mesh()
{
	this->num_v = 0;
	this->num_e = 0;
	this->num_f = 0;
}


Mesh::~Mesh()
{
}

void Mesh::addV(Vertex* v)
{
	if (get<1>(m_vertices.emplace(v, this->num_v++)))
	{
		this->l_vertices.push_back(v);
		this->storeVertLocation(v);
	}
}

void Mesh::addE(Edge* e)
{
	if (get<1>(this->m_edges.emplace(e, this->num_e++)))
	{
		this->l_edges.push_back(e);
	}
}

void Mesh::addF(Face* f)
{
	if (get<1>(this->m_faces.emplace(f, this->num_f++)))
	{
		this->l_faces.push_back(f);
		this->storeIndex(f);
		for (size_t i = 0; i < f->getVertices().size(); i++)
		{
			this->addV(f->getVertices()[i]);
			this->addE(new Edge(f->getVertices()[i], f->getVertices()[(i + 1) % 4]));
		}
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

//For drawing
//-------------------------------------
vector<GLfloat> Mesh::getLocations()
{
	return this->l_vLocations;
}

vector<GLuint> Mesh::getIndices()
{
	return this->l_indices;
}
//-------------------------------------
/*
	As Vertices are added to the mesh, store their location in a list that can be returned for drawing.
*/
void Mesh::storeVertLocation(Vertex* v)
{
	vector3f loc = v->getLocation();
	this->l_vLocations.push_back(get<0>(loc));
	this->l_vLocations.push_back(get<1>(loc));
	this->l_vLocations.push_back(get<2>(loc));
}

/*
	As faces are added to the mesh, store the corresponding incides to the vertices in the mesh vertex list.
*/
void Mesh::storeIndex(Face* f)
{
	vertex_l verts = f->getVertices();
	//cout << f->getVertices().size();
	for (size_t i = 0; i < verts.size(); i++)
	{
		//cout << m_vertices[verts[i]] << endl;
		this->num_i++;
		this->l_indices.push_back(m_vertices[verts[i]]);
	}
}

int Mesh::getNumInd()
{
	return this->num_i;
}