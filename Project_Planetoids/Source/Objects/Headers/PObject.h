#pragma once
#include "../../Headers/Planetoids.h"
#include "../../Mesh/Headers/PlanetMesh.h"
#include "../../Objects/Headers/Sky.h"
#include "../../Managers/Headers/ShaderManager.h"
#define al 16

extern GLuint atmoProgram, edgeProgram, terrainProgram;

#if !_DEBUG
__declspec(align(al)) class PObject
#else
class PObject
#endif
{
public:
	PObject();
	PObject(string name, GLfloat radius, int tesslvl, ShaderManager* sManager);
	~PObject();

	void init(string name, GLfloat radius, ShaderManager* sManager);
	void setName(string name);
	void setRadius(GLfloat radius);
	void update();
	void draw(Camera* camera);
	void setLoc(glm::vec3 loc);
	void setModelMatrix(const glm::mat4& modelMatrix);
	void changeLambda(int key, int action, int mods);

#if !_DEBUG
	void* operator new(size_t i);
	void operator delete(void *p);
#endif

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
	glm::vec3 cameraPos;
	float cHeight;

	PlanetMesh mesh;
	//Sky sky;

	GLuint vBuffer, cBuffer, nBuffer, iBuffer;
	
	GLuint u_PMatrix = 0, u_VMatrix = 0, u_MMatrix = 0, u_CameraPos = 0;
	GLuint a_position = 0, a_normal = 0, a_color = 0;

	GLuint u_PMatrix2 = 0, u_VMatrix2 = 0, u_MMatrix2 = 0;
	GLuint a_position2 = 0;

	struct Program
	{
		GLuint pId;
		GLuint u_PMatrix;
		GLuint u_VMatrix;
		GLuint u_MMatrix;
		GLuint a_Position;
		GLuint a_Color;
		GLuint a_Normal;
		GLuint Kr;
		GLuint Km;
		GLuint eSun;
		GLuint cameraPos;
		GLuint v3InvWaveLength;
		GLuint nSamples;
		GLuint radius;
	};

	Program groundFromAtmo, groundFromSpace, edgeShader, cp;

	void bufferTerrainObjects();

	void bindTerrainBuffers(int wireframe);
	void loadShader(Program& shader, string sName);
	void loadEdgeShader();

	void loadShaderVariables();
	
};

