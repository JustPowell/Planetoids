#include "../Headers/Sky.h"

Sky::Sky()
{
	this->setRadius(1.f);
	this->setLoc(glm::vec3(0, 0, 0));
	this->atmoMesh = PlanetMesh(this->radius, 5);
	this->modelMatrix = glm::mat4(1.0f);
	//loadShader(this->atmoEProgram, "edgeShader");
	//loadShader(this->atmoProgram, "atmoShader2");
	
	//this->loadShaderVariables();
	//this->bufferObjects();
	
}
Sky::Sky(GLfloat radius, ShaderManager* sManager, glm::vec3 loc = glm::vec3(0, 0, 0))
{
	this->sManager = sManager;
	this->setRadius(radius);
	this->setLoc(loc);
	this->atmoMesh = PlanetMesh(this->radius, 5);
	this->modelMatrix = glm::mat4(1.0f);

	sManager->createProgram("atmoShader2");
	sManager->createProgram("edgeShader2");
	
	this->loadShaderVariables();
	this->bufferObjects();
}


Sky::~Sky()
{
	//glDeleteShader(this->atmoEProgram);
	//glDeleteShader(this->atmoProgram);
}

void Sky::setRadius(GLfloat radius)
{
	this->radius = radius;
}

void Sky::update()
{
	//TODO
	
	this->modelMatrix = glm::translate(glm::mat4(1.f), this->loc);// *glm::rotate(glm::mat4(1.f), (float)glfwGetTime()*.05f, glm::vec3(0.f, 1.f, 0.f));
}

void Sky::updateShader(int key, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		this->sManager->reloadShader("atmoShader2");
		this->loadShaderVariables();
	}
}

void Sky::draw(Camera* camera)
{
	glm::vec3 camerapos = camera->getPos();
	float cHeight = (glm::length(camerapos) - 6400.f) / (6400.f * 1.025 - 6400.f);

	if (cHeight > 1.0)
	{
		glFrontFace(GL_CCW);
	}
	else{
		glFrontFace(GL_CW);
	}
	
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);

	glUseProgram(this->sManager->getProgram("edgeShader2"));
	this->bindBuffers(1);

	glUniformMatrix4fv(this->u_PaMatrix2, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->u_VaMatrix2, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->u_MaMatrix2, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	glDepthRange(0.0, 0.99999);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawElements(GL_QUADS, this->atmoMesh.getNumInd(), GL_UNSIGNED_INT, 0);

	//--------------------------------------------------------------------------------------
	

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(this->sManager->getProgram("atmoShader2"));
	this->bindBuffers(0);

	glUniformMatrix4fv(this->u_PaMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->u_VaMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->u_MaMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	glUniform3fv(this->u_CameraPos, 1, glm::value_ptr(camerapos));

	printf("\rCamera Pos: %f %f %f %f", cHeight, camerapos.x, camerapos.y, camerapos.z);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glDepthRange(0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_QUADS, this->atmoMesh.getNumInd(), GL_UNSIGNED_INT, 0);

	glDepthMask(GL_TRUE);
}

void Sky::setLoc(glm::vec3 loc)
{
	this->loc = loc;
}

void Sky::setModelMatrix(const glm::mat4& modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

GLfloat Sky::getRadius()
{
	return this->radius;
}

glm::mat4 Sky::getModelMatrix()
{
	return this->modelMatrix;
}

glm::vec3 Sky::getLoc()
{
	return this->loc;
}

/*GLuint Sky::getShader(int i)
{
	//?TODO?//
	if (i == 0)
		return this->atmoProgram;
	else
		return this->atmoEProgram;
}*/

PlanetMesh& Sky::getMesh()
{
	return this->atmoMesh;
}

void Sky::bufferObjects()
{
	glGenBuffers(1, &this->vaBuffer);
	glGenBuffers(1, &this->iaBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->vaBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->atmoMesh.getVerts().size() * 3), &this->atmoMesh.getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->iaBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*this->atmoMesh.getNumInd(), &this->atmoMesh.getIndices()[0], GL_STATIC_DRAW);
}

void Sky::bindBuffers(int i)
{
	if (i == 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vaBuffer);
		glVertexAttribPointer(this->a_position, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_position);
	}
	else if (i == 1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vaBuffer);
		glVertexAttribPointer(this->a_position2, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_position2);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iaBuffer);
}

void Sky::loadShaderVariables()
{
	this->u_PaMatrix = glGetUniformLocation(this->sManager->getProgram("atmoShader2"), "projection");
	this->u_VaMatrix = glGetUniformLocation(this->sManager->getProgram("atmoShader2"), "view");
	this->u_MaMatrix = glGetUniformLocation(this->sManager->getProgram("atmoShader2"), "model");
	this->u_CameraPos = glGetUniformLocation(this->sManager->getProgram("atmoShader2"), "cameraPos");

	this->u_PaMatrix2 = glGetUniformLocation(this->sManager->getProgram("edgeShader2"), "projection");
	this->u_VaMatrix2 = glGetUniformLocation(this->sManager->getProgram("edgeShader2"), "view");
	this->u_MaMatrix2 = glGetUniformLocation(this->sManager->getProgram("edgeShader2"), "model");

	this->a_position = glGetAttribLocation(this->sManager->getProgram("atmoShader2"), "position");
	this->a_position2 = glGetAttribLocation(this->sManager->getProgram("edgeShader2"), "position");
}