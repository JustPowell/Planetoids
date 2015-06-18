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

	string		getName();
	GLfloat		getRadius();
	glm::mat4	getModelMatrix();
	glm::vec3	getLoc();
	GLuint		getShader();
	PlanetMesh*	getMesh();

private:
	string name;
	GLfloat radius;

	glm::vec3 loc;
	glm::mat4 modelMatrix;

	GLuint faceProgram, edgeProgram;
	PlanetMesh* mesh = 0;

	GLuint vBuffer, cBuffer, nBuffer, iBuffer;
	GLuint u_PMatrix = 0, u_VMatrix = 0, u_MMatrix = 0;
	GLuint a_position = 0, a_normal = 0, a_color = 0;

	void bufferObjects();
	void bindBuffers(int wireframe);
	
	void loadShaderVariables();
	void loadShader(GLuint& shaderProgram, string shaderName);
	void createShader(GLuint& shaderProgram, const char* shadertext, GLuint& s_obj);
};

