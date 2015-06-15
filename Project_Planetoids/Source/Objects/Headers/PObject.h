#pragma once
#include "../../Headers/Planetoids.h"
#include "../../Mesh/Headers/PlanetMesh.h"

class PObject
{
public:
	PObject();
	~PObject();

	void update();
	void draw();

	void setLoc(glm::vec3 loc);
	glm::vec3 getLoc();

	void setModelMatrix(const glm::mat4& modelMatrix);
	glm::mat4 getModelMatrix();

	GLuint getShader();
	PlanetMesh getMesh();

private:
	GLfloat radius;

	glm::vec3 loc;
	glm::mat4 modelMatrix;

	GLuint shaderProgram;
	PlanetMesh mesh;

	void loadShader(GLuint shaderProgram);
};

