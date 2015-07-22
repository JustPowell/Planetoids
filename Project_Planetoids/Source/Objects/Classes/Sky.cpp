#include "../Headers/Sky.h"
#include <windows.h>

Sky::Sky()
{
	this->setRadius(1.f);
	this->setLoc(glm::vec3(0, 0, 0));
	this->atmoMesh = PlanetMesh(this->radius, 6);
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
	//this->atmoMesh = PlanetMesh(this->radius, 7, 0, 1);
	this->spaceMesh = PlanetMesh(this->radius, 7);
	this->modelMatrix = glm::mat4(1.0f);

	sManager->createProgram("atmoShader2");
	sManager->createProgram("edgeShader2");
	sManager->createProgram("atmoFromSpace");
	
	this->loadShaderVariables();
	this->cp = this->atmoFromGround;
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

void Sky::update(Camera* camera)
{
	//TODO
	this->cHeight = (glm::length(this->cameraPos) - 10.f) / (10.f * 1.025 - 10.f);
	if (this->cHeight > 1.0)
	{
		this->cp = this->atmoFromSpace;
	}
	else if (this->cHeight <= 1.0)
	{
		this->cp = this->atmoFromGround;
	}
	
	//glm::vec3 ray = glm::normalize(this->cameraPos - glm::vec3(0, 0, 0));
	//this->modelMatrix = /*glm::translate(this->modelMatrix, glm::vec3(0, 0, 0)) **/ glm::rotate(this->modelMatrix, .001f, glm::vec3(0, 1, 0));
	this->modelMatrix = glm::translate(glm::mat4(1.f), this->loc);

}

void Sky::updateShader(int key, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		this->sManager->reloadShader("atmoShader2");
		this->sManager->reloadShader("atmoFromSpace");
		this->loadShaderVariables();
	}
	if (key == GLFW_KEY_1 && mods == GLFW_MOD_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->v3InvWaveLength.r -= .001;
		if (this->sManager->v3InvWaveLength.r < .380f)
		{
			this->sManager->v3InvWaveLength.r = .380f;
		}
	}
	else if (key == GLFW_KEY_1 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->v3InvWaveLength.r += .001;
		if (this->sManager->v3InvWaveLength.r > .780f)
		{
			this->sManager->v3InvWaveLength.r = .780f;
		}
	}
	if (key == GLFW_KEY_2 && mods == GLFW_MOD_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->v3InvWaveLength.g -= .001;
		if (this->sManager->v3InvWaveLength.g < .380f)
		{
			this->sManager->v3InvWaveLength.g = .380f;
		}
	}
	else if (key == GLFW_KEY_2 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->v3InvWaveLength.g += .001;
		if (this->sManager->v3InvWaveLength.g > .780f)
		{
			this->sManager->v3InvWaveLength.g = .780f;
		}
	}
	if (key == GLFW_KEY_3 && mods == GLFW_MOD_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->v3InvWaveLength.b -= .001;
		if (this->sManager->v3InvWaveLength.b < .380f)
		{
			this->sManager->v3InvWaveLength.b = .380f;
		}
	}
	else if (key == GLFW_KEY_3 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->v3InvWaveLength.b += .001;
		if (this->sManager->v3InvWaveLength.b > .780f)
		{
			this->sManager->v3InvWaveLength.b = .780f;
		}
	}

	if (key == GLFW_KEY_4 && mods == GLFW_MOD_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->Kr -= .0001;
		if (this->sManager->Kr < .0f)
		{
			this->sManager->Kr = .0f;
		}
	}
	else if (key == GLFW_KEY_4 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->Kr += .0001;
	}
	if (key == GLFW_KEY_5 && mods == GLFW_MOD_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->Km -= .0001;
		if (this->sManager->Km < .0f)
		{
			this->sManager->Km = .0f;
		}
	}
	else if (key == GLFW_KEY_5 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->Km += .0001;
	}
	if (key == GLFW_KEY_6 && mods == GLFW_MOD_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->eSun -= 1.f;
		if (this->sManager->eSun < .0f)
		{
			this->sManager->eSun = .0f;
		}
	}
	else if (key == GLFW_KEY_6 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		this->sManager->eSun += 1.f;
	}

	if (key == GLFW_KEY_BACKSLASH && (action == GLFW_PRESS))
	{
		if (this->drawWire)
			this->drawWire = 0;
		else
			this->drawWire = 1;
	}

	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		this->sManager->nSamples++;
	}
	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		this->sManager->nSamples--;
		if (this->sManager->nSamples < 0)
		{
			this->sManager->nSamples = 0;
		}
	}
}

void Sky::draw(Camera* camera)
{
	this->cameraPos = camera->getPos();
	int numInd, s = 1;
	//numInd = this->spaceMesh.getNumInd();
	if (this->cHeight > 1.0)
	{
		glFrontFace(GL_CW);
		numInd = this->spaceMesh.getNumInd();
		s = 1;
	}
	else{
		glFrontFace(GL_CW);
		numInd = this->spaceMesh.getNumInd();
		s = 1;
	}
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glUseProgram(this->edgeShader.pId);
	this->bindBuffers(1, s);

	glUniformMatrix4fv(this->edgeShader.u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->edgeShader.u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->edgeShader.u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	glDepthRange(0.0, 0.99999);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (this->drawWire)
		glDrawElements(GL_QUADS, numInd, GL_UNSIGNED_INT, 0);

	//--------------------------------------------------------------------------------------
	
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(this->cp.pId);
	this->bindBuffers(0, s);

	glUniformMatrix4fv(this->cp.u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(this->cp.u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(this->cp.u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	glUniform3fv(this->cp.cameraPos, 1, glm::value_ptr(this->cameraPos));
	glUniform1f(this->cp.Kr, this->sManager->Kr);
	glUniform1f(this->cp.Km, this->sManager->Km);
	glUniform1f(this->cp.eSun, this->sManager->eSun);
	glUniform3fv(this->cp.v3InvWaveLength, 1, glm::value_ptr(glm::vec3(1 / pow(this->sManager->v3InvWaveLength.r, 4), 1 / pow(this->sManager->v3InvWaveLength.g, 4), 1 / pow(this->sManager->v3InvWaveLength.b, 4))));
	glUniform1i(this->cp.nSamples, this->sManager->nSamples);
	glUniform1f(this->cp.radius, this->radius / 1.025);
	printf("Camera Pos: %f %f %f %f \n %f %f %f \n Kr: %f\nKm: %f\neSun: %f\nSpeed: %f\nnSamples: %i", 
			this->cHeight, this->cameraPos.x, this->cameraPos.y, this->cameraPos.z, 
			this->sManager->v3InvWaveLength.r, this->sManager->v3InvWaveLength.g, this->sManager->v3InvWaveLength.b,
			this->sManager->Kr, this->sManager->Km, this->sManager->eSun,
			camera->getSpeed(),
			this->sManager->nSamples);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = 0, coord.Y = 0;
	SetConsoleCursorPosition(hStdOut, coord);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glDepthRange(0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_QUADS, numInd, GL_UNSIGNED_INT, 0);

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

	glGenBuffers(1, &this->vaBuffer2);
	glGenBuffers(1, &this->iaBuffer2);

	glBindBuffer(GL_ARRAY_BUFFER, this->vaBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->atmoMesh.getVerts().size() * 3), &this->atmoMesh.getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->iaBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*this->atmoMesh.getNumInd(), &this->atmoMesh.getIndices()[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->vaBuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->spaceMesh.getVerts().size() * 3), &this->spaceMesh.getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->iaBuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*this->spaceMesh.getNumInd(), &this->spaceMesh.getIndices()[0], GL_STATIC_DRAW);
	
}

void Sky::bindBuffers(int i, int s)
{
	GLuint v, ind;
	if (s == 0)
	{
		v = this->vaBuffer;
		ind = this->iaBuffer;
	}
	else if (s == 1)
	{
		v = this->vaBuffer2;
		ind = this->iaBuffer2;
	}

	if (i == 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, v);
		glVertexAttribPointer(this->cp.a_Position, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->cp.a_Position);
	}
	else if (i == 1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, v);
		glVertexAttribPointer(this->edgeShader.a_Position, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->edgeShader.a_Position);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind);
}

void Sky::loadShaderVariables()
{
	this->loadShader(this->atmoFromGround, "atmoShader2");
	this->loadShader(this->atmoFromSpace, "atmoFromSpace");
	this->loadEdgeShader();
}

void Sky::loadShader(Program& shader, string sName)
{
	shader.pId = this->sManager->getProgram(sName);
	shader.u_PMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "projection");
	shader.u_VMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "view");
	shader.u_MMatrix = glGetUniformLocation(this->sManager->getProgram(sName), "model");
	shader.Kr = glGetUniformLocation(this->sManager->getProgram(sName), "Kr");
	shader.Km = glGetUniformLocation(this->sManager->getProgram(sName), "Km");
	shader.eSun = glGetUniformLocation(this->sManager->getProgram(sName), "ESun");
	shader.v3InvWaveLength = glGetUniformLocation(this->sManager->getProgram(sName), "v3InvWaveLength");
	shader.cameraPos = glGetUniformLocation(this->sManager->getProgram(sName), "cameraPos");
	shader.a_Position = glGetAttribLocation(this->sManager->getProgram(sName), "position");
	shader.nSamples = glGetUniformLocation(this->sManager->getProgram(sName), "nSamples");
	shader.radius = glGetUniformLocation(this->sManager->getProgram(sName), "fInnerRadius");
}

void Sky::loadEdgeShader()
{
	this->edgeShader.pId = this->sManager->getProgram("edgeShader");
	this->edgeShader.u_PMatrix = glGetUniformLocation(this->sManager->getProgram("edgeShader2"), "projection");
	this->edgeShader.u_VMatrix = glGetUniformLocation(this->sManager->getProgram("edgeShader2"), "view");
	this->edgeShader.u_MMatrix = glGetUniformLocation(this->sManager->getProgram("edgeShader2"), "Matrix");
	this->edgeShader.a_Position = glGetAttribLocation(this->sManager->getProgram("edgeShader2"), "position");
}