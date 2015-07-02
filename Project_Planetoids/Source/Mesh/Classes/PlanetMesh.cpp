#include "../Headers/PlanetMesh.h"

PlanetMesh::PlanetMesh()
{
	this->setRadius(0);
	this->setSubdivisionLvl(0);
}

PlanetMesh::PlanetMesh(GLfloat r, int sublvl, int random)
{
	this->random = random;
	this->setRadius(r);
	this->setSubdivisionLvl(sublvl);
	this->buildPlanet();
}

PlanetMesh::~PlanetMesh()
{
}

void PlanetMesh::setRadius(GLfloat radius)
{
	this->radius = radius;
}

void PlanetMesh::setSubdivisionLvl(int sublvl)
{
	this->sublvl = sublvl;
}

void PlanetMesh::buildPlanet()
{
	this->initVertices(this->sublvl);
	this->initCube();
	this->subdivide(this->sublvl);
	this->toSphere();
}

void PlanetMesh::initVertices(int sublvl)
{
	GLfloat r = this->radius;
	
	Vertex *vert = new Vertex(vector3f(-r, r, r));
	this->addV(vert);
	
	vert = new Vertex(vector3f(r, r, r));
	this->addV(vert);
	
	vert = new Vertex(vector3f(r, -r, r));
	this->addV(vert);
	
	vert = new Vertex(vector3f(-r, -r, r));
	this->addV(vert);
	//-------------------------------------------------------------

	vert = new Vertex(vector3f(-r, r, -r));
	this->addV(vert);
	
	vert = new Vertex(vector3f(r, r, -r));
	this->addV(vert);
	
	vert = new Vertex(vector3f(r, -r, -r));
	this->addV(vert);
	
	vert = new Vertex(vector3f(-r, -r, -r));
	this->addV(vert);
	
}

PlanetMesh::side* PlanetMesh::getSide(int idx)
{
	return this->cubeside[idx];
}

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
	//--------------------------------------
	
}

void PlanetMesh::subdivide(int sublvl)
{
	unordered_map<Edge*, Vertex*> newVerts;
	face_l oldFaces;
	edge_l oldEdges;

	for (int i = 0; i < sublvl; i++)
	{
		oldFaces.insert(oldFaces.end(), this->l_faces.begin(), this->l_faces.end());
		oldEdges.insert(oldEdges.end(), this->l_edges.begin(), this->l_edges.end());
		this->m_edges.clear();
		this->m_faces.clear();

		face_l templist = this->l_faces;

		this->l_faces.clear();
		this->l_edges.clear();

		this->num_e = 0;
		this->num_f = 0;

		size_t size;
		size = templist.size();
		
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
			this->addEdges(f0);

			this->addF(f1);
			this->addEdges(f1);

			this->addF(f2);
			this->addEdges(f2);

			this->addF(f3);
			this->addEdges(f3);
		}
	}
	clearVector<edge_l>(oldEdges);
	clearVector<face_l>(oldFaces);
	oldEdges.clear();
	oldFaces.clear();
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
	cent.x = (face->getVertices()[0]->getLocation().x + face->getVertices()[1]->getLocation().x + face->getVertices()[2]->getLocation().x + face->getVertices()[3]->getLocation().x) / 4;
	cent.y = (face->getVertices()[0]->getLocation().y + face->getVertices()[1]->getLocation().y + face->getVertices()[2]->getLocation().y + face->getVertices()[3]->getLocation().y) / 4;
	cent.z = (face->getVertices()[0]->getLocation().z + face->getVertices()[1]->getLocation().z + face->getVertices()[2]->getLocation().z + face->getVertices()[3]->getLocation().z) / 4;

	Vertex* faceCent = new Vertex(cent);
	newVertList.push_back(faceCent);

	return newVertList;
}

void PlanetMesh::toSphere()
{
	int count = 0;
	int count2 = 10;
	for (size_t i = 0; i < this->num_v; i++)
	{
		count++;
		count2++;
		vector3f newloc;
		vector3f loc = this->l_vertices[i]->getLocation();

		GLfloat theta, phi;
		theta = acos((loc.z / sqrt( pow(loc.x, 2) + pow(loc.y, 2) + pow(loc.z, 2))));
		phi = atan2(loc.y, loc.x);

		int randn;
		if (this->random && (count2 % 10 == 0))
		{
			randn = 75;//(rand() % 50);
			count2 = 0;
		}
		else
			randn = 0;

		newloc.x = (this->radius + randn) * sin(theta) * cos(phi);
		newloc.y = (this->radius + randn) * sin(theta) * sin(phi);
		newloc.z = (this->radius + randn) * cos(theta);

		this->l_vertices[i]->setLocation(newloc);
	}
	this->updateLocations();
}