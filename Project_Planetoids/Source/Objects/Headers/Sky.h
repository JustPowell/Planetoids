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
	void update();
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
	ShaderManager* sManager;
	GLfloat radius;
	PlanetMesh atmoMesh;
	//GLuint atmoProgram = 0, atmoEProgram = 0;
	GLuint vaBuffer = 0, iaBuffer = 0;
	GLuint u_PaMatrix = 0, u_VaMatrix = 0, u_MaMatrix = 0, u_CameraPos = 0, u_PaMatrix2 = 0, u_VaMatrix2 = 0, u_MaMatrix2 = 0;
	GLuint a_position = 0, a_position2 = 0;
	glm::vec3 loc;
	glm::mat4 modelMatrix;

	void bufferObjects();
	void bindBuffers(int i);
	void loadShaderVariables();
};

