#include "PObject.h"


PObject::PObject()
{
}

PObject::PObject(string name, int id)
{
	this->setName(name);
	this->setId(id);
}

PObject::~PObject()
{
}

void PObject::setName(string name)
{
	this->name = name;
}

void PObject::setId(int id)
{
	this->id = id;
}

void PObject::setVertices(vector<Vertex> vertices)
{
	this->vertices = new GLfloat[this->vertexList.size()];
	for (int i = 0; i < this->vertexList.size(); i++)
	{
		GLfloat* vert = this->vertexList[i].getLocation();
		for (int j = 0; j < 3; j++)
		{
			this->vertices[j + (this->vertexList.size()*i)] = vert[j];
		}
	}
}

void PObject::setNormals()
{
	this->normals = new GLfloat[this->vertexList.size()];
	for (int i = 0; i < this->vertexList.size(); i++)
	{
		GLfloat* norm = this->vertexList[i].getNormal();
		for (int j = 0; j < 3; j++)
		{
			this->normals[j + (this->vertexList.size()*i)] = norm[j];
		}
	}
}

void PObject::setColors()
{
	this->colors = new GLfloat[this->vertexList.size()];
	for (int i = 0; i < this->vertexList.size(); i++)
	{
		GLfloat* col = this->vertexList[i].getColor();
		for (int j = 0; j < 3; j++)
		{
			this->colors[j + (this->vertexList.size()*i)] = col[j];
		}
	}
}

void PObject::setIndices(GLubyte *indices)
{
	this->indices = indices;
}

std::string PObject::getName()
{
	return this->name;
}

int	PObject::getId()
{
	return this->id;
}

GLfloat* PObject::getVertices()
{
	return this->vertices;
}

GLfloat* PObject::getNormals()
{
	return this->normals;
}

GLfloat* PObject::getColors()
{
	return this->colors;
}

GLubyte* PObject::getIndices()
{
	return this->indices;
}