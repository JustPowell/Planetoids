#include "../Headers/PlanetMesh.h"

PlanetMesh::PlanetMesh(GLfloat r, int sublvl)
{
	this->radius = r;
	this->initVertices(sublvl);
	this->initCube();
	this->subdivide(sublvl);
	this->toSphere();
} 


PlanetMesh::~PlanetMesh()
{
}

void PlanetMesh::initVertices(int sublvl)
{
	GLfloat r = this->radius;
	
	Vertex *vert = new Vertex(vector3f(-r, r, r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(-r, r, r), vert);

	vert = new Vertex(vector3f(r, r, r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(r, r, r), vert);

	vert = new Vertex(vector3f(r, -r, r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(r, -r, r), vert);

	vert = new Vertex(vector3f(-r, -r, r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(-r, -r, r), vert);
	//-------------------------------------------------------------

	vert = new Vertex(vector3f(-r, r, -r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(-r, r, -r), vert);

	vert = new Vertex(vector3f(r, r, -r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(r, r, -r), vert);

	vert = new Vertex(vector3f(r, -r, -r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(r, -r, -r), vert);

	vert = new Vertex(vector3f(-r, -r, -r));
	this->addV(vert);
	//this->initVerts.push_back(vert);
	//this->vertexTable.emplace(vector3f(-r, -r, -r), vert);
	
}

void PlanetMesh::addVert(Vertex *vert)
{
	//this->vertexTable.emplace(vert->getLocation(), vert);
}


PlanetMesh::side* PlanetMesh::getSide(int idx)
{
	return this->cubeside[idx];
}

/*Quadtree* PlanetMesh::getQuad(int idx)
{
	return this->quadtrees[idx];
}*/

void PlanetMesh::initCube()
{
	
	//Init sides----------------------------
	this->cubeside.push_back(new side);
	this->cubeside.push_back(new side);
	this->cubeside.push_back(new side);
	this->cubeside.push_back(new side);
	this->cubeside.push_back(new side);
	this->cubeside.push_back(new side);
	//--------------------------------------

	//Side 0--------------------------------
	this->cubeside[0]->top = this->cubeside[4];
	this->cubeside[0]->bot = this->cubeside[5];
	this->cubeside[0]->left = this->cubeside[3];
	this->cubeside[0]->right = this->cubeside[1];
	Face* f = new Face(this->getVerts()[0], this->getVerts()[3], this->getVerts()[2], this->getVerts()[1]);
	this->addF(f);
	this->addEdges(f);
	this->cubeside[0]->faceList.push_back(f);
	//this->quadtrees.push_back(new Quadtree(this->cubeside[0]->faceList[0]));
	//--------------------------------------
	
	//Side 1--------------------------------
	this->cubeside[1]->top = this->cubeside[4];
	this->cubeside[1]->bot = this->cubeside[5];
	this->cubeside[1]->left = this->cubeside[0];
	this->cubeside[1]->right = this->cubeside[2];
	f = new Face(this->getVerts()[1], this->getVerts()[2], this->getVerts()[6], this->getVerts()[5]);
	this->addF(f);
	this->addEdges(f);
	this->cubeside[1]->faceList.push_back(f);
	//this->quadtrees.push_back(new Quadtree(this->cubeside[1]->faceList[0]));
	//--------------------------------------

	//Side 2--------------------------------
	this->cubeside[2]->top = this->cubeside[4];
	this->cubeside[2]->bot = this->cubeside[5];
	this->cubeside[2]->left = this->cubeside[1];
	this->cubeside[2]->right = this->cubeside[3];
	f = new Face(this->getVerts()[5], this->getVerts()[6], this->getVerts()[7], this->getVerts()[4]);
	this->addF(f);
	this->addEdges(f);
	this->cubeside[2]->faceList.push_back(f);
	//this->quadtrees.push_back(new Quadtree(this->cubeside[2]->faceList[0]));
	//--------------------------------------

	//Side 3--------------------------------
	this->cubeside[3]->top = this->cubeside[4];
	this->cubeside[3]->bot = this->cubeside[5];
	this->cubeside[3]->left = this->cubeside[2];
	this->cubeside[3]->right = this->cubeside[0];
	f = new Face(this->getVerts()[4], this->getVerts()[7], this->getVerts()[3], this->getVerts()[0]);
	this->addF(f);
	this->addEdges(f);
	this->cubeside[3]->faceList.push_back(f);
	//this->quadtrees.push_back(new Quadtree(this->cubeside[3]->faceList[0]));
	//--------------------------------------

	//Side 4--------------------------------
	this->cubeside[4]->top = this->cubeside[2];
	this->cubeside[4]->bot = this->cubeside[0];
	this->cubeside[4]->left = this->cubeside[3];
	this->cubeside[4]->right = this->cubeside[1];
	f = new Face(this->getVerts()[4], this->getVerts()[0], this->getVerts()[1], this->getVerts()[5]);
	this->addF(f);
	this->addEdges(f);
	this->cubeside[4]->faceList.push_back(f);
	//this->quadtrees.push_back(new Quadtree(this->cubeside[4]->faceList[0]));
	//--------------------------------------

	//Side 5--------------------------------
	this->cubeside[5]->top = this->cubeside[0];
	this->cubeside[5]->bot = this->cubeside[2];
	this->cubeside[5]->left = this->cubeside[3];
	this->cubeside[5]->right = this->cubeside[1];
	f = new Face(this->getVerts()[3], this->getVerts()[7], this->getVerts()[6], this->getVerts()[2]);
	this->addF(f);
	this->addEdges(f);
	this->cubeside[5]->faceList.push_back(f);
	//this->quadtrees.push_back(new Quadtree(this->cubeside[5]->faceList[0]));
	//--------------------------------------
	
}
/*
void PlanetMesh::subdivide(int sublvl)
{
	for (int i = 0; i < sublvl; i++)
	{
		for (size_t s = 0, c_size = this->cubeside.size(); s < c_size; ++s)
		{
			face_l tempFacel;
			int size = this->cubeside[s]->faceList.size();

			for (int f = 0; f < size; f++)
			{
				Face *face = this->cubeside[s]->faceList[f];

				vertex_l newVertl = this->calcNewVerts(face);
				Face *f0 = new Face(face->getVertices()[0], newVertl[0], newVertl[4], newVertl[3]);
				Face *f1 = new Face(newVertl[0], face->getVertices()[1], newVertl[1], newVertl[4]);
				Face *f2 = new Face(newVertl[3], newVertl[4], newVertl[2], face->getVertices()[3]);
				Face *f3 = new Face(newVertl[4], newVertl[1], face->getVertices()[2], newVertl[2]);

				tempFacel.push_back(f0);
				tempFacel.push_back(f1);
				tempFacel.push_back(f2);
				tempFacel.push_back(f3);
			}
			cubeside[s]->faceList = tempFacel;
		}
	}
}
*/
void PlanetMesh::subdivide(int sublvl)
{
	unordered_map<Edge*, Vertex*> newVerts;
	for (int i = 0; i < sublvl; i++)
	{
		this->m_edges.clear();
		this->m_faces.clear();

		face_l templist = this->l_faces;
		this->l_faces.clear();
		this->l_edges.clear();

		this->num_e = 0;
		this->num_f = 0;

		size_t size = templist.size();
		for (size_t s = 0; s < size; s++)
		{
			Face* face = templist[s];
			vertex_l newVertl = this->calcNewVerts(newVerts, face);
			
			for (size_t k = 0; k < newVertl.size(); k++)
			{
				this->addV(newVertl[k]);
			}

			Face *f0 = new Face(face->getVertices()[0], newVertl[0], newVertl[4], newVertl[3]);
			Face *f1 = new Face(newVertl[0], face->getVertices()[1], newVertl[1], newVertl[4]);
			Face *f2 = new Face(newVertl[3], newVertl[4], newVertl[2], face->getVertices()[3]);
			Face *f3 = new Face(newVertl[4], newVertl[1], face->getVertices()[2], newVertl[2]);

			this->addF(f0);
			//templist.push_back(f0);
			this->addEdges(f0);

			this->addF(f1);
			//templist.push_back(f1);
			this->addEdges(f1);

			this->addF(f2);
			//templist.push_back(f2);
			this->addEdges(f2);

			this->addF(f3);
			//templist.push_back(f3);
			this->addEdges(f3);
		}
		//this->l_faces = templist;
	}
	this->updateIndex();
}

vertex_l PlanetMesh::calcNewVerts(unordered_map<Edge*, Vertex*>& newVerts, Face *face)
{
	vertex_l newVertList;

	for (size_t i = 0; i < face->getEdges().size(); i++)
	{
		Edge* e = face->getEdges()[i];
		Vertex* cent = new Vertex(getCentroid(e->getVert(0), e->getVert(1)));
		if (!get<1>(newVerts.emplace(e, cent)))
		{
			newVertList.push_back(newVerts.find(e)->second);
		}
		else
		{
			newVertList.push_back(cent);
		}
	}

	vector3f cent;
	get<0>(cent) = (get<0>(face->getVertices()[0]->getLocation()) + get<0>(face->getVertices()[1]->getLocation()) + get<0>(face->getVertices()[2]->getLocation()) + get<0>(face->getVertices()[3]->getLocation())) / 4;
	get<1>(cent) = (get<1>(face->getVertices()[0]->getLocation()) + get<1>(face->getVertices()[1]->getLocation()) + get<1>(face->getVertices()[2]->getLocation()) + get<1>(face->getVertices()[3]->getLocation())) / 4;
	get<2>(cent) = (get<2>(face->getVertices()[0]->getLocation()) + get<2>(face->getVertices()[1]->getLocation()) + get<2>(face->getVertices()[2]->getLocation()) + get<2>(face->getVertices()[3]->getLocation())) / 4;

	Vertex* faceCent = new Vertex(cent);
	newVertList.push_back(faceCent);

	return newVertList;
}

void PlanetMesh::toSphere()
{
	//vertexMap newTable;
	int count = 0;
	for (size_t i = 0; i < this->num_v; i++)
	//for (auto it = this->vertexTable.begin(); it != this->vertexTable.end(); ++it)
	{
		count++;
		vector3f newloc;
		vector3f loc = this->l_vertices[i]->getLocation();

		GLfloat theta, phi;
		theta = acos((get<2>(loc) / sqrt( pow(get<0>(loc), 2) + pow(get<1>(loc), 2) + pow(get<2>(loc), 2))));
		phi = atan2(get<1>(loc), get<0>(loc));

		get<0>(newloc) = this->radius * sin(theta) * cos(phi);
		get<1>(newloc) = this->radius * sin(theta) * sin(phi);
		get<2>(newloc) = this->radius * cos(theta);

		this->l_vertices[i]->setLocation(newloc);
	}
	this->updateLocations();
}