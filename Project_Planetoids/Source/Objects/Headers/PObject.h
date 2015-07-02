#pragma once
#include "../../Headers/Planetoids.h"
#include "../../Mesh/Headers/PlanetMesh.h"

class PObject
{
public:
	PObject(string name, GLfloat radius);
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

private:
	int mult = 1;
	string name;
	GLfloat radius;

	float lambda = 500.f;
	glm::vec3 loc;
	glm::mat4 modelMatrix;

	GLuint faceProgram, edgeProgram, atmoProgram, atmoEProgram;
	PlanetMesh mesh, atmo;

	GLuint vBuffer, cBuffer, nBuffer, iBuffer;
	GLuint vaBuffer, caBuffer, naBuffer, iaBuffer;
	GLuint u_PMatrix = 0, u_VMatrix = 0, u_MMatrix = 0, u_CameraPos = 0, f_lambda = 0;
	GLuint a_position = 0, a_normal = 0, a_color = 0;

	void bufferTerrainObjects();
	void bufferAtmoObjects();
	void bindTerrainBuffers(int wireframe);
	void bindAtmoBuffers();

	void loadShaderVariables();
	void loadShader(GLuint& shaderProgram, string shaderName);
	void createShader(GLuint& shaderProgram, const char* shadertext, GLuint& s_obj);
};

