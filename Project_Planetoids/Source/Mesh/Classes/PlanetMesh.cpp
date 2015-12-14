#include "../Headers/PlanetMesh.h"

PlanetMesh::PlanetMesh()
{
	this->setRadius(0);
	this->setSubdivisionLvl(0);
}

PlanetMesh::PlanetMesh(GLfloat r, int sublvl, int random, int atmo)
{
	this->random = random;
	this->setRadius(r);
	this->setSubdivisionLvl(sublvl);
	this->buildPlanet(atmo);
	//this->sim = Simplex();
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

void PlanetMesh::buildPlanet(int atmo)
{
	this->initVertices(this->sublvl);
	this->initCube(atmo);
	if (atmo)
		this->initAtmoCube();
	else{
		this->subdivide(this->sublvl);
		this->genPlates();
	}
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

void PlanetMesh::initAtmoCube()
{
	GLfloat r = this->radius;
	
	 Vertex *vert = new Vertex(vector3f(-r / 2.0, r, r / 2.0));
	this->addV(vert);

	vert = new Vertex(vector3f(r / 2.0, r, r / 2.0));
	this->addV(vert);

	vert = new Vertex(vector3f(r / 2.0, r, -r / 2.0));
	this->addV(vert);

	vert = new Vertex(vector3f(-r / 2.0, r, -r / 2.0));
	this->addV(vert);
	//------------------------------------------------------
	vert = new Vertex(vector3f(-r / 4.0, r, r / 4.0));
	this->addV(vert);

	vert = new Vertex(vector3f(r / 4.0, r, r / 4.0));
	this->addV(vert);

	vert = new Vertex(vector3f(r / 4.0, r, -r / 4.0));
	this->addV(vert);

	vert = new Vertex(vector3f(-r / 4.0, r, -r / 4.0));
	this->addV(vert);

	//---------------------------------------------------------------
	// New Side

	/*Face* f = new Face(this->getVerts()[11], this->getVerts()[8], this->getVerts()[9], this->getVerts()[10]);
	this->addF(f);
	this->addEdges(f);
	*/
	Face* f = new Face(this->getVerts()[15], this->getVerts()[12], this->getVerts()[13], this->getVerts()[14]);
	this->addF(f);
	this->addEdges(f);

	f = new Face(this->getVerts()[11], this->getVerts()[8], this->getVerts()[12], this->getVerts()[15]);
	this->addF(f);
	this->addEdges(f);

	f = new Face(this->getVerts()[12], this->getVerts()[8], this->getVerts()[9], this->getVerts()[13]);
	this->addF(f);
	this->addEdges(f);

	f = new Face(this->getVerts()[14], this->getVerts()[13], this->getVerts()[9], this->getVerts()[10]);
	this->addF(f);
	this->addEdges(f);

	f = new Face(this->getVerts()[11], this->getVerts()[15], this->getVerts()[14], this->getVerts()[10]);
	this->addF(f);
	this->addEdges(f);
	this->subdivide(this->sublvl);
	
	//---------------------------------------------------------------
	// New Side
	f = new Face(this->getVerts()[4], this->getVerts()[0], this->getVerts()[8], this->getVerts()[11]);
	this->addF(f);
	this->addEdges(f);

	f = new Face(this->getVerts()[8], this->getVerts()[0], this->getVerts()[1], this->getVerts()[9]);
	this->addF(f);
	this->addEdges(f);

	f = new Face(this->getVerts()[10], this->getVerts()[9], this->getVerts()[1], this->getVerts()[5]);
	this->addF(f);
	this->addEdges(f);

	f = new Face(this->getVerts()[4], this->getVerts()[11], this->getVerts()[10], this->getVerts()[5]);
	this->addF(f);
	this->addEdges(f);
	
}

PlanetMesh::side* PlanetMesh::getSide(int idx)
{
	return this->cubeside[idx];
}

void PlanetMesh::initCube(int atmo)
{
	if (!atmo)
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
}

void PlanetMesh::subdivide(int sublvl)
{
	unordered_map<Edge*, Vertex*> newVerts;
	face_l oldFaces;
	edge_l oldEdges;

	for (int i = 0; i < sublvl; i++)
	{
		for (size_t i = 0; i < this->num_v; i++)
		{
			this->l_vertices[i]->rstHeight();
		}

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
			
			//f0->setpNum(rand() % 3);
			//f1->setpNum(rand() % 3);
			//f2->setpNum(rand() % 3);
			//f3->setpNum(rand() % 3);
			/*
				This is for changing the base mesh during generation.
			*/
			//f0->setHeight((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * ((rand() % 2) * 2 - 1));
			//f1->setHeight((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * ((rand() % 2) * 2 - 1));
			//f2->setHeight((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * ((rand() % 2) * 2 - 1));
			//f3->setHeight((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * ((rand() % 2) * 2 - 1));

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
		
		//this->l_vertices[i]->avgHeight(); //When changing the base mesh.
		
		vector3f loc = this->l_vertices[i]->getLocation();

		GLfloat theta, phi;
		theta = acos((loc.z / sqrt( pow(loc.x, 2) + pow(loc.y, 2) + pow(loc.z, 2))));
		phi = atan2(loc.y, loc.x);

		double randn;
		if (this->random)// && (count2 % 10 == 0))
		{
			//randn = .05*sim.noise(loc.x, loc.y, loc.z);//(rand() % 50);
			//cout << randn << endl;
			count2 = 0;
		}
		else
			randn = 0;

		newloc.x = (this->radius /*+ this->l_vertices[i]->getHeight()*/) * sin(theta) * cos(phi);
		newloc.y = (this->radius /*+ this->l_vertices[i]->getHeight()*/) * sin(theta) * sin(phi);
		newloc.z = (this->radius /*+ this->l_vertices[i]->getHeight()*/) * cos(theta);

		this->l_vertices[i]->setLocation(newloc);
	}
	this->updateLocations();
}

void PlanetMesh::genPlates()
{
	int numP = 9;
	int sizeF = this->l_faces.size();
	f_map assignFaces;

	for (int i = 0; i < numP; i++)
	{
		vector<Face*>* p = new vector<Face*>();
		int f = rand() % sizeF;

		while (!get<1>(assignFaces.emplace(this->l_faces[f], 1)))
		{
			f = rand() & sizeF;
		}

		p->push_back(this->l_faces[f]);
		p->at(0)->setpNum(i);
		this->platesList.push_back(p);
	}

	
	this->assignPlates(assignFaces);
	this->updateColors();
}

void PlanetMesh::assignPlates(f_map& assignFaces)
{
	int numP = 9;
	int sizeF = this->l_faces.size();
	edge_l edges;
	face_l faces;
	
	while (assignFaces.size() < sizeF)
	{
		for (int i = 0; i < numP; i++)
		{
			if (this->platesList.at(i)->size() != 0)
			{
				int r = (rand() % this->platesList.at(i)->size());
				Face* f = this->platesList.at(i)->at(r);
				while (this->checkFace(f))
				{
					this->platesList[i]->erase(this->platesList[i]->begin() + (r));
					break;
					r = (rand() % this->platesList.at(i)->size());
					f = this->platesList.at(i)->at(rand() % this->platesList.at(i)->size());
				}

				edges = f->getEdges();

				faces = edges[rand() % 4]->getAdjFaces();

				if (get<1>(assignFaces.emplace(faces[0], 1)))
				{
					if (faces[0]->getpNum() == -1){
						faces[0]->setpNum(faces[1]->getpNum());
						platesList.at(i)->push_back(faces[0]);
					}
				}
				else
				{
					if (faces[1]->getpNum() == -1)
					{
						assignFaces.emplace(faces[1], 1);
						faces[1]->setpNum(faces[0]->getpNum());
						platesList.at(i)->push_back(faces[1]);
					}
				}
			}
		}
	}
}

int PlanetMesh::checkFace(Face* f)
{
	int full = 1;
	edge_l edges = f->getEdges();
	for (int i = 0; i < 4; i++)
	{
		face_l faces = edges[i]->getAdjFaces();
		if (faces[0]->getpNum() < 0 || faces[1]->getpNum() < 0)
		{
			full = 0;
		}
	}
	return full;
}