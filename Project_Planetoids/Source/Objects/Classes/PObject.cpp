#include "../Headers/PObject.h"


PObject::PObject(string name, GLfloat radius, ShaderManager* sManager)
{
	this->sManager = sManager;
	this->setName(name);
	this->setRadius(radius);
	this->mesh = PlanetMesh(radius, 5, 1);
	
	this->modelMatrix = glm::mat4(1.0f);
	this->setLoc(glm::vec3(0.f, 0.f, 0.f));
	
	this->sManager->createProgram(name);
	this->sManager->createProgram("edgeShader");

	this->loadShaderVariables();
	this->bufferTerrainObjects();

	this->sky = Sky(radius * 1.025, this->sManager, this->loc);
}


PObject::~PObject()
{
}

void PObject::setName(string name)
{
	this->name = name;
}

void PObject::setRadius(GLfloat radius)
{
	this->radius = radius;
}

void PObject::changeLambda(int key, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		this->sManager->reloadShader("shaderTest");
		this->loadShaderVariables();
	}
	if (key == GLFW_KEY_EQUAL && mods == GLFW_MOD_SHIFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->lambda += 10.f;
	}
	else if (key == GLFW_KEY_MINUS && mods == GLFW_MOD_SHIFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->lambda -= 10.f;
	}

	else if (key == GLFW_KEY_EQUAL && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->lambda += 1.f;
	}
	else if (key == GLFW_KEY_MINUS && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		this->lambda -= 1.f;
	}

	if (this->lambda > 780.f)
	{
		this->lambda = 780.f;
	}
	else if (this->lambda < 380.f)
	{
		this->lambda = 380.f;
	}
}

void PObject::update()
{
	/*if (this->lambda >= 780.0f || this->lambda <= 380.0f)
	{
		this->mult *= -1;
	}
	this->lambda += (.2500000f * mult);
	if (this->lambda > 780.f)
	{
		this->lambda = 780.f;
	}
	else if (this->lambda < 380.f)
	{
		this->lambda = 380.f;
	}*/
	//printf("\rLambda: %f", this->lambda);
	this->modelMatrix = glm::translate(glm::mat4(1.f), this->loc);// *glm::rotate(glm::mat4(1.f), (float)glfwGetTime()*.05f, glm::vec3(0.f, 1.f, 0.f));
	this->sky.update();
}

void PObject::draw(Camera* camera)
{
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(this->sManager->getProgram("shaderTest"));
	this->bindTerrainBuffers(0);

	glUniformMatrix4fv(this->u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glDepthRange(0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_QUADS, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);
	//--------------------------------------------------------------------------------------
	glUseProgram(this->sManager->getProgram("edgeShader"));
	this->bindTerrainBuffers(1);

	glUniformMatrix4fv(this->u_PMatrix2, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->u_VMatrix2, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->u_MMatrix2, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDepthRange(0.0, 0.99999);

	glDrawElements(GL_QUADS, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);
	//--------------------------------------------------------------------------------------
	
	
	
	//--------------------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------------------
}

void PObject::setLoc(glm::vec3 loc)
{
	this->loc = loc;
	this->sky.setLoc(loc);
}

void PObject::setModelMatrix(const glm::mat4& modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

string PObject::getName()
{
	return this->name;
}

GLfloat PObject::getRadius()
{
	return this->radius;
}

glm::mat4 PObject::getModelMatrix()
{
	return this->modelMatrix;
}

glm::vec3 PObject::getLoc()
{
	return this->loc;
}

Sky& PObject::getSky()
{
	return this->sky;
}

void PObject::bufferTerrainObjects()
{
	glGenBuffers(1, &this->vBuffer);
	glGenBuffers(1, &this->cBuffer);
	glGenBuffers(1, &this->nBuffer);
	glGenBuffers(1, &this->iBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->mesh.getVerts().size() * 3), &this->mesh.getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->cBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->mesh.getVerts().size() * 3), &this->mesh.getColors()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->nBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->mesh.getVerts().size() * 3), &this->mesh.getNormals()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->iBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*this->mesh.getNumInd(), &this->mesh.getIndices()[0], GL_STATIC_DRAW);
}

void PObject::bindTerrainBuffers(int wireframe)
{
	if (wireframe == 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
		glVertexAttribPointer(this->a_position, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_position);

		glBindBuffer(GL_ARRAY_BUFFER, this->cBuffer);
		glVertexAttribPointer(this->a_color, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_color);

		glBindBuffer(GL_ARRAY_BUFFER, this->nBuffer);
		glVertexAttribPointer(this->a_normal, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_normal);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
		glVertexAttribPointer(this->a_position, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_position2);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iBuffer);
}

void PObject::loadShaderVariables()
{
	this->u_PMatrix = glGetUniformLocation(this->sManager->getProgram("shaderTest"), "projection");
	this->u_VMatrix = glGetUniformLocation(this->sManager->getProgram("shaderTest"), "view");
	this->u_MMatrix = glGetUniformLocation(this->sManager->getProgram("shaderTest"), "model");

	this->u_PMatrix2 = glGetUniformLocation(this->sManager->getProgram("edgeShader"), "projection");
	this->u_VMatrix2 = glGetUniformLocation(this->sManager->getProgram("edgeShader"), "view");
	this->u_MMatrix2 = glGetUniformLocation(this->sManager->getProgram("edgeShader"), "model");

	this->a_position = glGetAttribLocation(this->sManager->getProgram("shaderTest"), "position");
	this->a_normal = glGetAttribLocation(this->sManager->getProgram("shaderTest"), "normal");
	this->a_color = glGetAttribLocation(this->sManager->getProgram("shaderTest"), "color");

	this->a_position2 = glGetAttribLocation(this->sManager->getProgram("edgeShader"), "position");
}

PlanetMesh PObject::getMesh()
{
	return this->mesh;
}