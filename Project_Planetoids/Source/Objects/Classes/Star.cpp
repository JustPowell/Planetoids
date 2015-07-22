#include "../Headers/Star.h"


Star::Star(string name, GLfloat radius, ShaderManager* sManager)
{
	this->sManager = sManager;
	this->setName(name);
	this->setRadius(radius);
	this->mesh = PlanetMesh(radius, 5, 0);

	this->modelMatrix = glm::mat4(1.0f);
	this->setLoc(glm::vec3(0.f, 0.f, 0.f));

	this->sManager->createProgram(name);

	this->loadShader(this->starShader, name);
	this->bufferObjects();
}


Star::~Star()
{
}

void Star::setName(string name)
{
	this->name = name;
}

void Star::setRadius(GLfloat radius)
{
	this->radius = radius;
}

void Star::setLoc(glm::vec3 loc)
{
	this->loc = loc;
}

void Star::setModelMatrix(const glm::mat4& modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

string Star::getName()
{
	return this->name;
}

GLfloat Star::getRadius()
{
	return this->radius;
}

glm::mat4 Star::getModelMatrix()
{
	return this->modelMatrix;
}

glm::vec3 Star::getLoc()
{
	return this->loc;
}

PlanetMesh Star::getMesh()
{
	return this->mesh;
}

void Star::update()
{
	this->modelMatrix = glm::translate(glm::mat4(1.f), this->loc);// *glm::rotate(glm::mat4(1.f), (float)glfwGetTime()*.05f, glm::vec3(0.f, 1.f, 0.f));
}

void Star::draw(Camera* camera)
{
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(this->starShader.pId);
	this->bindBuffers();

	glUniformMatrix4fv(this->starShader.u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->starShader.u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->starShader.u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));

	//glDepthRange(0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_QUADS, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);
}

void Star::bindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
	glVertexAttribPointer(this->starShader.a_Position, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(this->starShader.a_Position);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iBuffer);
}

void Star::bufferObjects()
{
	glGenBuffers(1, &this->vBuffer);
	glGenBuffers(1, &this->iBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->mesh.getVerts().size() * 3), &this->mesh.getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->iBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*this->mesh.getNumInd(), &this->mesh.getIndices()[0], GL_STATIC_DRAW);
}

void Star::loadShader(Program& shader, string sName)
{
	shader.pId = this->sManager->getProgram(sName);
	shader.u_PMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "projection");
	shader.u_VMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "view");
	shader.u_MMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "model");
	shader.a_Position = glGetAttribLocation(this->sManager->getProgram(sName), "position");
}