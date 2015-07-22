#pragma once
#include "../../Headers/Planetoids.h"
#include "../../Mesh/Headers/PlanetMesh.h"
#include "../../Managers/Headers/ShaderManager.h"

extern GLuint atmoProgram, edgeProgram, terrainProgram;

class Sky
{
public:
	Sky();
	Sky(GLfloat radius, ShaderManager* sManager, glm::vec3 loc);
	~Sky();

	void setRadius(GLfloat radius);
	void update(Camera* camera);
	void updateShader(int key, int action, int mods);
	void draw(Camera* camera);
	void setLoc(glm::vec3 loc);
	void setModelMatrix(const glm::mat4& modelMatrix);

	GLfloat getRadius();
	glm::mat4 getModelMatrix();
	glm::vec3 getLoc();
	GLuint getShader(int i);
	PlanetMesh& getMesh();

private:
	int drawWire = 0;
	ShaderManager* sManager;
	GLfloat radius;
	PlanetMesh atmoMesh, spaceMesh;

	GLuint vaBuffer = 0, iaBuffer = 0;
	GLuint vaBuffer2 = 0, iaBuffer2 = 0;
	
	glm::vec3 loc;
	glm::mat4 modelMatrix;
	glm::vec3 cameraPos;
	float cHeight = 0;
	//glm::vec3 v3InvWaveLength = glm::vec3(.650, .570, .475);
	//float Kr = .0025f;
	//float Km = .0010f;
	//float eSun = 30.f;

	struct Program
	{
		GLuint pId;
		GLuint u_PMatrix;
		GLuint u_VMatrix;
		GLuint u_MMatrix;
		GLuint a_Position;
		GLuint Kr;
		GLuint Km;
		GLuint eSun;
		GLuint cameraPos;
		GLuint v3InvWaveLength;
		GLuint nSamples;
		GLuint radius;
	};

	Program atmoFromGround, atmoFromSpace, edgeShader, cp;
	
	void bufferObjects();
	void bindBuffers(int i, int s = 0);
	void loadShaderVariables();
	void loadShader(Program& shader, string sName);
	void loadEdgeShader();
};

