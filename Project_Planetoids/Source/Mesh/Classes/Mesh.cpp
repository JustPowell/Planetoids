#include "../Headers/Mesh.h"


Mesh::Mesh()
{
	this->num_v = 0;
	this->num_e = 0;
	this->num_f = 0;
	this->l_vertices.resize(0);
	this->l_edges.resize(0);
	this->l_faces.resize(0);
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
	else
	{
		num_v--;
	}
}

void Mesh::addE(Edge* e)
{
	if (get<1>(this->m_edges.emplace(e, this->num_e++)))
	{
		this->l_edges.push_back(e);
	}
	else
	{
		//if (!l_edges[this->m_edges[e]]->getAdjFaces().empty() && !e->getAdjFaces().empty())
		//	l_edges[this->m_edges[e]]->addAdjFace(e->getAdjFaces().at(0));
		e = l_edges[this->m_edges[e]];
		num_e--;
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
		}
		for (size_t i = 0; i < f->getEdges().size(); i++)
		{
			this->addE(f->getEdges()[i]);
		}
	}
	else
	{
		num_f--;
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
//TODO
void Mesh::addEdges(Face* f)
{
	for (size_t i = 0; i < f->getVertices().size(); i++)
	{
		Edge* e = new Edge(f->getVertices()[i], f->getVertices()[(i + 1) % 4]);
		e = this->checkEdge(e);
		this->addE(e);
		f->addEdge(e);
	}
}

Edge* Mesh::checkEdge(Edge* e)
{
	if (m_edges.find(e) != m_edges.end())
	{
		return l_edges[m_edges[e]];
	}
	else
	{
		return e;
	}
}