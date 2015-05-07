#include "PlanetMesh.h"


PlanetMesh::PlanetMesh(GLfloat r, int sublvl)
{
	this->radius = r;
	this->initVertices();
	this->initCube();
	this->subdivide(sublvl);
	this->toSphere();
} 


PlanetMesh::~PlanetMesh()
{
}

void PlanetMesh::initVertices()
{
	GLfloat r = this->radius;
	Vertex *vert = new Vertex(tup3f(-r, r, r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(-r, r, r), vert);

	vert = new Vertex(tup3f(r, r, r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(r, r, r), vert);

	vert = new Vertex(tup3f(r, -r, r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(r, -r, r), vert);

	vert = new Vertex(tup3f(-r, -r, r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(-r, -r, r), vert);
	//-------------------------------------------------------------

	vert = new Vertex(tup3f(-r, r, -r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(-r, r, -r), vert);

	vert = new Vertex(tup3f(r, r, -r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(r, r, -r), vert);

	vert = new Vertex(tup3f(r, -r, -r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(r, -r, -r), vert);

	vert = new Vertex(tup3f(-r, -r, -r));
	this->initVerts.push_back(vert);
	this->vertexTable.emplace(tup3f(-r, -r, -r), vert);
}

void PlanetMesh::addVert(Vertex *vert)
{
	this->vertexTable.emplace(vert->getLocation(), vert);
}


PlanetMesh::side* PlanetMesh::getSide(int idx)
{
	return this->cubeside[idx];
}

Quadtree* PlanetMesh::getQuad(int idx)
{
	return this->quadtrees[idx];
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
	this->cubeside[0]->faceList.push_back(new Face(this->initVerts[0], this->initVerts[1], this->initVerts[2], this->initVerts[3]));
	this->quadtrees.push_back(new Quadtree(this->cubeside[0]->faceList[0]));
	//--------------------------------------
	
	//Side 1--------------------------------
	this->cubeside[1]->top = this->cubeside[4];
	this->cubeside[1]->bot = this->cubeside[5];
	this->cubeside[1]->left = this->cubeside[0];
	this->cubeside[1]->right = this->cubeside[2];
	this->cubeside[1]->faceList.push_back(new Face(this->initVerts[1], this->initVerts[5], this->initVerts[6], this->initVerts[2]));
	this->quadtrees.push_back(new Quadtree(this->cubeside[1]->faceList[0]));
	//--------------------------------------

	//Side 2--------------------------------
	this->cubeside[2]->top = this->cubeside[4];
	this->cubeside[2]->bot = this->cubeside[5];
	this->cubeside[2]->left = this->cubeside[1];
	this->cubeside[2]->right = this->cubeside[3];
	this->cubeside[2]->faceList.push_back(new Face(this->initVerts[5], this->initVerts[4], this->initVerts[7], this->initVerts[6]));
	this->quadtrees.push_back(new Quadtree(this->cubeside[2]->faceList[0]));
	//--------------------------------------

	//Side 3--------------------------------
	this->cubeside[3]->top = this->cubeside[4];
	this->cubeside[3]->bot = this->cubeside[5];
	this->cubeside[3]->left = this->cubeside[2];
	this->cubeside[3]->right = this->cubeside[0];
	this->cubeside[3]->faceList.push_back(new Face(this->initVerts[4], this->initVerts[0], this->initVerts[3], this->initVerts[7]));
	this->quadtrees.push_back(new Quadtree(this->cubeside[3]->faceList[0]));
	//--------------------------------------

	//Side 4--------------------------------
	this->cubeside[4]->top = this->cubeside[2];
	this->cubeside[4]->bot = this->cubeside[0];
	this->cubeside[4]->left = this->cubeside[3];
	this->cubeside[4]->right = this->cubeside[1];
	this->cubeside[4]->faceList.push_back(new Face(this->initVerts[4], this->initVerts[5], this->initVerts[1], this->initVerts[0]));
	this->quadtrees.push_back(new Quadtree(this->cubeside[4]->faceList[0]));
	//--------------------------------------

	//Side 5--------------------------------
	this->cubeside[5]->top = this->cubeside[0];
	this->cubeside[5]->bot = this->cubeside[2];
	this->cubeside[5]->left = this->cubeside[3];
	this->cubeside[5]->right = this->cubeside[1];
	this->cubeside[5]->faceList.push_back(new Face(this->initVerts[3], this->initVerts[2], this->initVerts[6], this->initVerts[7]));
	this->quadtrees.push_back(new Quadtree(this->cubeside[5]->faceList[0]));
	//--------------------------------------
}

void PlanetMesh::subdivide(int sublvl)
{
	for (int i = 0; i < sublvl; i++)
	{
		for (int s = 0; s < this->cubeside.size(); s++)
		{
			Face::face_l tempFacel;
			int size = this->cubeside[s]->faceList.size();

			/*vector<Quad*> quadlist;
			if (i == 0)
			{
				vector<Quad*> temp;
				temp.push_back(quadtrees[s]->getRoot());
				quadlist = temp;
			}
			else{
				quadlist = this->quadtrees[s]->getQuadlist(i);
			}*/

			for (int f = 0; f < size; f++)
			{
				Face *face = this->cubeside[s]->faceList[f];
				//Quad *quad = quadlist[f];

				Vertex::vertex_l newVertl = this->calcNewVerts(face);
				Face *f0 = new Face(face->getVertices()[0], newVertl[0], newVertl[4], newVertl[3]);
				Face *f1 = new Face(newVertl[0], face->getVertices()[1], newVertl[1], newVertl[4]);
				Face *f2 = new Face(newVertl[3], newVertl[4], newVertl[2], face->getVertices()[3]);
				Face *f3 = new Face(newVertl[4], newVertl[1], face->getVertices()[2], newVertl[2]);

				tempFacel.push_back(f0);
				//quad->addNode(0, f0);

				tempFacel.push_back(f1);
				//quad->addNode(1, f1);

				tempFacel.push_back(f2);
				//quad->addNode(2, f2);

				tempFacel.push_back(f3);
				//quad->addNode(3, f3);
			}
			cubeside[s]->faceList = tempFacel;
		}
	}
}

Vertex::vertex_l PlanetMesh::calcNewVerts(Face *face)
{
	Vertex::vertex_l newVertList;
	Vertex *v0 = face->getVertices()[0];
	Vertex *v1 = face->getVertices()[1];
	Vertex *v2 = face->getVertices()[2];
	Vertex *v3 = face->getVertices()[3];

	tup3f cl[5];
	cl[0] = v0->getCentroid(v1);
	cl[1] = v1->getCentroid(v2);
	cl[2] = v2->getCentroid(v3);
	cl[3] = v3->getCentroid(v0);
	cl[4] = v0->getCentroid(v1, v2, v3);
	
	for (int i = 0; i < 5; i++)
	{
		Vertex *newVert = new Vertex(cl[i]);
		if (!get<1>(vertexTable.emplace(cl[i], newVert)))
		{
			newVertList.push_back(vertexTable.find(cl[i])->second);
		}
		else
		{
			this->addVert(newVert);
			newVertList.push_back(newVert);

		}
	}

	return newVertList;
}

void PlanetMesh::toSphere()
{
	vertexMap newTable;
	int count = 0;
	for (auto it = this->vertexTable.begin(); it != this->vertexTable.end(); ++it)
	{
		count++;
		tup3f newloc;
		tup3f loc = it->second->getLocation();

		GLfloat theta, phi;
		theta = acos((get<2>(loc) / sqrt( pow(get<0>(loc), 2) + pow(get<1>(loc), 2) + pow(get<2>(loc), 2))));
		phi = atan2(get<1>(loc), get<0>(loc));
		//cout << this->radius << " " << theta << " " << phi << endl;

		get<0>(newloc) = this->radius * sin(theta) * cos(phi);
		get<1>(newloc) = this->radius * sin(theta) * sin(phi);
		get<2>(newloc) = this->radius * cos(theta);

		it->second->setLocation(newloc);
		newTable.emplace(it->second->getLocation(), it->second);
	}
	vertexTable = newTable;
}
