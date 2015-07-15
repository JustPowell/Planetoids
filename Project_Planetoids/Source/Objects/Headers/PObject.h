#pragma once
#include "../../Headers/Planetoids.h"
#include "../../Mesh/Headers/PlanetMesh.h"
#include "../../Objects/Headers/Sky.h"
#include "../../Managers/Headers/ShaderManager.h"

extern GLuint atmoProgram, edgeProgram, terrainProgram;

class PObject
{
public:
	PObject(string name, GLfloat radius, ShaderManager* sManager);
	~PObject();

	void setName(string name);
	void setRadius(GLfloat radius);
	void update();
	void draw(Camera* camera);
	void setLoc(glm::vec3 loc);
	void setModelMatrix(const glm::mat4& modelMatrix);
	void changeLambda(int key, int action, int mods);

	string		getName();
	GLfloat		getRadius();
	glm::mat4	getModelMatrix();
	glm::vec3	getLoc();
	GLuint		getShader();
	PlanetMesh	getMesh();
	Sky&			getSky();

private:
	ShaderManager* sManager;
	int mult = 1;
	string name;
	GLfloat radius;

	float lambda = 500.f;
	glm::vec3 loc;
	glm::mat4 modelMatrix;

	PlanetMesh mesh;
	Sky sky;

	GLuint vBuffer, cBuffer, nBuffer, iBuffer;
	
	GLuint u_PMatrix = 0, u_VMatrix = 0, u_MMatrix = 0;
	GLuint a_position = 0, a_normal = 0, a_color = 0;

	GLuint u_PMatrix2 = 0, u_VMatrix2 = 0, u_MMatrix2 = 0;
	GLuint a_position2 = 0;

	void bufferTerrainObjects();

	void bindTerrainBuffers(int wireframe);


	void loadShaderVariables();
	
};

