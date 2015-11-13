#include "../Headers/PObject.h"
PObject::PObject()
{

}

PObject::PObject(string name, GLfloat radius, int tesslvl, ShaderManager* sManager)
{
	this->sManager = sManager;
	this->setName(name);
	this->setRadius(radius);
	this->mesh = PlanetMesh(radius, tesslvl, 0);
	
	this->modelMatrix = glm::mat4(1.0f);
	this->setLoc(glm::vec3(0.f, 0.f, 0.f));
	
	this->sManager->createProgram(name);
	this->sManager->createProgram("groundFromAtmo");
	this->sManager->createProgram("edgeShader");

	this->loadShaderVariables();
	this->bufferTerrainObjects();

	//this->sky = Sky(radius * 1.025, this->sManager, this->loc);
}


PObject::~PObject()
{
}

void PObject::init(string name, GLfloat radius, ShaderManager* sManager)
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
		this->sManager->reloadShader(this->getName());
		this->sManager->reloadShader("groundFromAtmo");
		this->sManager->reloadShader("edgeShader");
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

	if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
	{
		this->setLoc(glm::vec3(0.f, 100.f, 0.f));
	}
	if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS)
	{
		this->setLoc(glm::vec3(0.f, 0.f, 0.f));
	}
}

void PObject::update()
{
	this->cHeight = ((glm::length(this->cameraPos) - glm::length(this->loc)) - 10.f) / (10.f * 1.025f - 10.f);
	if (this->cHeight > 1.0)
	{
		this->cp = this->groundFromSpace;
	}
	else if (this->cHeight <= 1.0)
	{
		//this->cp = this->groundFromAtmo;
		this->cp = this->groundFromSpace;
	}
	this->modelMatrix = glm::translate(glm::mat4(1.f), this->loc);// *glm::rotate(glm::mat4(1.f), (float)glfwGetTime()*.05f, glm::vec3(0.f, 1.f, 0.f));
}

void PObject::draw(Camera* camera)
{
	this->cameraPos = camera->getPos();
	
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(this->cp.pId);
	this->bindTerrainBuffers(0);

	glUniformMatrix4fv(this->cp.u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->cp.u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->cp.u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	
	glUniform3fv(this->cp.cameraPos, 1, glm::value_ptr(camera->getPos()));
	/*glUniform1f(this->cp.Kr, this->sManager->Kr);
	glUniform1f(this->cp.Km, this->sManager->Km);
	glUniform1f(this->cp.eSun, this->sManager->eSun);
	glUniform3fv(this->cp.v3InvWaveLength, 1, glm::value_ptr(glm::vec3(1 / pow(this->sManager->v3InvWaveLength.r, 4), 1 / pow(this->sManager->v3InvWaveLength.g, 4), 1 / pow(this->sManager->v3InvWaveLength.b, 4))));
	glUniform1i(this->cp.nSamples, this->sManager->nSamples);
	glUniform1f(this->cp.radius, this->radius);
	*/
	glDepthRange(0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (tess)
	{
		glPatchParameteri(GL_PATCH_VERTICES, 4);
		glDrawElements(GL_PATCHES, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);
	}
	else
		glDrawElements(GL_QUADS, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);


	//--------------------------------------------------------------------------------------
	glUseProgram(this->edgeShader.pId);
	this->bindTerrainBuffers(1);

	glUniformMatrix4fv(this->edgeShader.u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->edgeShader.u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->edgeShader.u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDepthRange(0.0, 0.99999);

	glDrawElements(GL_QUADS, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);
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
		glVertexAttribPointer(this->cp.a_Position, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->cp.a_Position);

		glBindBuffer(GL_ARRAY_BUFFER, this->cBuffer);
		glVertexAttribPointer(this->cp.a_Color, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->cp.a_Color);

		glBindBuffer(GL_ARRAY_BUFFER, this->nBuffer);
		glVertexAttribPointer(this->cp.a_Normal, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->cp.a_Normal);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
		glVertexAttribPointer(this->edgeShader.a_Position, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_position2);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iBuffer);
}

void PObject::loadShaderVariables()
{
	this->loadShader(this->groundFromAtmo, "groundFromAtmo");
	this->loadShader(this->groundFromSpace, this->getName());
	this->loadEdgeShader();
}

PlanetMesh PObject::getMesh()
{
	return this->mesh;
}

void PObject::loadShader(Program& shader, string sName)
{
	shader.pId = this->sManager->getProgram(sName);
	shader.u_PMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "projection");
	shader.u_VMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "view");
	shader.u_MMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "model");
	/*shader.Kr = glGetUniformLocation(this->sManager->getProgram(sName), "Kr");
	shader.Km = glGetUniformLocation(this->sManager->getProgram(sName), "Km");
	shader.eSun = glGetUniformLocation(this->sManager->getProgram(sName), "ESun");
	shader.v3InvWaveLength = glGetUniformLocation(this->sManager->getProgram(sName), "v3InvWaveLength");
	*/
	shader.cameraPos = glGetUniformLocation(this->sManager->getProgram(sName), "cameraPos");
	
	shader.a_Position = glGetAttribLocation(this->sManager->getProgram(sName), "position");
	
	shader.a_Color = glGetAttribLocation(this->sManager->getProgram(sName), "color");
	/*shader.a_Normal = glGetAttribLocation(this->sManager->getProgram(sName), "normal");
	shader.nSamples = glGetUniformLocation(this->sManager->getProgram(sName), "nSamples");
	shader.radius = glGetUniformLocation(this->sManager->getProgram(sName), "fInnerRadius");*/
}

void PObject::loadEdgeShader()
{
	this->edgeShader.pId = this->sManager->getProgram("edgeShader");
	this->edgeShader.u_PMatrix = glGetUniformLocation(this->sManager->getProgram("edgeShader"), "projection");
	this->edgeShader.u_VMatrix = glGetUniformLocation(this->sManager->getProgram("edgeShader"), "view");
	this->edgeShader.u_MMatrix = glGetUniformLocation(this->sManager->getProgram("edgeShader"), "model");
	this->edgeShader.a_Position = glGetAttribLocation(this->sManager->getProgram("edgeShader"), "position");
}

#if !_DEBUG
void* PObject::operator new(size_t i)
{
	return _mm_malloc(i, al);
}

void PObject::operator delete(void* p)
{
	_mm_free(p);
}
#endif