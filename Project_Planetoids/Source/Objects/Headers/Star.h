#pragma once
#include "../../Headers/Planetoids.h"
#include "../../Mesh/Headers/PlanetMesh.h"
#include "../../Managers/Headers/ShaderManager.h"
class Star
{
public:
	Star(string name, GLfloat radius, ShaderManager* sManager);
	~Star();

	void setName(string name);
	void setRadius(GLfloat radius);
	void update();
	void draw(Camera* camera);
	void setLoc(glm::vec3 loc);
	void setModelMatrix(const glm::mat4& modelMatrix);

	string		getName();
	GLfloat		getRadius();
	glm::mat4	getModelMatrix();
	glm::vec3	getLoc();
	GLuint		getShader();
	PlanetMesh	getMesh();

private:
	ShaderManager* sManager;
	string name;
	GLfloat radius;

	glm::vec3 loc;
	glm::mat4 modelMatrix;
	glm::vec3 cameraPos;

	PlanetMesh mesh;
	GLuint vBuffer, iBuffer;

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
	};

	Program starShader;

	void bufferObjects();
	void bindBuffers();
	void loadShader(Program& shader, string sName);
};

