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
		this->storeColor(v);
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

vector<GLfloat> Mesh::getNormals()
{
	return this->l_normals;
}

vector<GLfloat> Mesh::getColors()
{
	return this->l_colors;
}

//-------------------------------------
/*
	As Vertices are added to the mesh, store their location in a list that can be returned for drawing.
*/
void Mesh::storeVertLocation(Vertex* v)
{
	vector3f loc = v->getLocation();
	this->l_vLocations.push_back(loc.x);
	this->l_vLocations.push_back(loc.y);
	this->l_vLocations.push_back(loc.z);
}

void Mesh::storeNormals(Vertex* v)
{
	vector3f nor = v->getNormal();
	this->l_normals.push_back(nor.x);
	this->l_normals.push_back(nor.y);
	this->l_normals.push_back(nor.z);
}

void Mesh::storeColor(Vertex* v)
{
	vector3f col = v->getColor();
	this->l_colors.push_back(col.x);
	this->l_colors.push_back(col.y);
	this->l_colors.push_back(col.z);
}

/*
	As faces are added to the mesh, store the corresponding incides to the vertices in the mesh vertex list.
*/
void Mesh::storeIndex(Face* f)
{
	vertex_l verts = f->getVertices();
	for (size_t i = 0; i < verts.size(); i++)
	{
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

void Mesh::updateLocations()
{
	this->l_vLocations.clear();
	for (size_t i = 0; i < this->l_vertices.size(); i++)
	{
		this->storeVertLocation(this->l_vertices[i]);
	}
	for (size_t i = 0; i < this->l_faces.size(); i++)
	{
		this->calcFaceNormal(this->l_faces[i]);
	}
	this->calcNormals();
}

void Mesh::updateIndex()
{
	this->l_indices.clear();
	this->num_i = 0;
	for (size_t i = 0; i < this->l_faces.size(); i++)
	{
		this->storeIndex(this->l_faces[i]);
	}
}

void Mesh::updateColors()
{
	this->l_colors.clear();
	for (size_t i = 0; i < this->l_vertices.size(); i++)
	{
		this->storeColor(this->l_vertices[i]);
	}
}

void Mesh::calcNormals()
{
	
	for (size_t i = 0; i < this->l_faces.size(); i++)
	{
		Face* f = this->l_faces[i];
		for (size_t k = 0; k < f->getVertices().size(); k++)
		{
			Vertex* v = f->getVertices()[k];
			v->setNormal(v->getNormal() + f->getNormal());
		}
	}
	for (size_t j = 0; j < this->l_vertices.size(); j++)
	{
		glm::vec3 norm;
		Vertex* v = this->l_vertices[j];
		norm.x = v->getNormal().x / 4;
		norm.y = v->getNormal().y / 4;
		norm.z = v->getNormal().z / 4;
		v->setNormal(norm);
		this->storeNormals(v);
	}
}

void Mesh::calcFaceNormal(Face* f)
{
	glm::vec3 v0 = f->getVertices()[0]->getLocation();
	glm::vec3 v1 = f->getVertices()[1]->getLocation();
	glm::vec3 v2 = f->getVertices()[2]->getLocation();
	glm::vec3 v3 = f->getVertices()[3]->getLocation();

	glm::vec3 a, b;
	a = v0 - v1;
	b = v2 - v1;

	glm::vec3 c, d;
	c = v3 - v0;
	d = v1 - v0;

	glm::vec3 norm = glm::normalize(glm::cross(a, b) + glm::cross(c, d));
	
	f->setNormal(norm);
}