#include "../Headers/PObject.h"


PObject::PObject(string name, GLfloat radius)
{
	this->setName(name);
	this->setRadius(radius);
	this->mesh = PlanetMesh(radius, 5, 1);
	this->atmo = PlanetMesh(radius + 1600, 5);
	this->modelMatrix = glm::mat4(1.0f);
	this->setLoc(glm::vec3(0.f, 0.f, 0.f));

	this->loadShader(this->faceProgram, name);
	this->loadShader(this->edgeProgram, "edgeShader");
	this->loadShader(this->atmoProgram, "atmoShader");
	this->loadShader(this->atmoEProgram, "edgeShader");
	this->loadShaderVariables();
	this->bufferTerrainObjects();
	this->bufferAtmoObjects();
}


PObject::~PObject()
{
	glDeleteProgram(this->faceProgram);
	glDeleteProgram(this->edgeProgram);
	glDeleteProgram(this->atmoProgram);
	glDeleteProgram(this->atmoEProgram);
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
		glDeleteShader(this->atmoProgram);
		this->loadShader(this->atmoProgram, "atmoShader");
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
	printf("\rLambda: %f", this->lambda);
	this->modelMatrix = glm::translate(glm::mat4(1.f), this->loc);// *glm::rotate(glm::mat4(1.f), (float)glfwGetTime()*.05f, glm::vec3(0.f, 1.f, 0.f));
}

void PObject::draw(Camera* camera)
{
	//--------------------------------------------------------------------------------------
	/*glUseProgram(this->edgeProgram);
	this->bindTerrainBuffers(1);
	glUniformMatrix4fv(u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthRange(0.0, 0.99995);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
	//glDrawElements(GL_QUADS, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);

	//--------------------------------------------------------------------------------------
	glUseProgram(this->faceProgram);
	this->bindTerrainBuffers(0);
	glUniformMatrix4fv(u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, .99994);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_QUADS, this->mesh.getNumInd(), GL_UNSIGNED_INT, 0);

	//--------------------------------------------------------------------------------------
	glUseProgram(this->atmoEProgram);
	this->bindAtmoBuffers();
	glUniformMatrix4fv(u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(u_MMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthRange(0.0, 0.99995);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_QUADS, this->atmo.getNumInd(), GL_UNSIGNED_INT, 0);
	
	//--------------------------------------------------------------------------------------
	glUseProgram(this->atmoProgram);
	this->bindAtmoBuffers();
	glUniformMatrix4fv(u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(u_MMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));
	
	glUniform3fv(u_CameraPos, 1, glm::value_ptr(camera->getPos()));
	printf(" Camera Pos: %f %f %f", camera->getPos().x, camera->getPos().y, camera->getPos().z);
	glUniform1f(f_lambda, this->lambda);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	glDepthRange(0.0, .99996);
	//glEnable(GL_BLEND);
	//glDepthFunc(GL_LEQUAL);
	//glDisable(GL_CULL_FACE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_QUADS, this->atmo.getNumInd(), GL_UNSIGNED_INT, 0);
	
	//--------------------------------------------------------------------------------------
	glDepthMask(GL_TRUE);
}

void PObject::setLoc(glm::vec3 loc)
{
	this->loc = loc;
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

void PObject::bufferAtmoObjects()
{
	glGenBuffers(1, &this->vaBuffer);
	glGenBuffers(1, &this->caBuffer);
	glGenBuffers(1, &this->naBuffer);
	glGenBuffers(1, &this->iaBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->vaBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->atmo.getVerts().size() * 3), &this->atmo.getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->caBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->atmo.getVerts().size() * 3), &this->atmo.getColors()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->naBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->atmo.getVerts().size() * 3), &this->atmo.getNormals()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->iaBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*this->atmo.getNumInd(), &this->atmo.getIndices()[0], GL_STATIC_DRAW);
}

void PObject::bindTerrainBuffers(int wireframe)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
	glVertexAttribPointer(this->a_position, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(this->a_position);

	if (!wireframe)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->cBuffer);
		glVertexAttribPointer(this->a_color, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_color);

		glBindBuffer(GL_ARRAY_BUFFER, this->nBuffer);
		glVertexAttribPointer(this->a_normal, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(this->a_normal);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iBuffer);
}

void PObject::bindAtmoBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vaBuffer);
	glVertexAttribPointer(this->a_position, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(this->a_position);

	glBindBuffer(GL_ARRAY_BUFFER, this->caBuffer);
	glVertexAttribPointer(this->a_color, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(this->a_color);

	glBindBuffer(GL_ARRAY_BUFFER, this->naBuffer);
	glVertexAttribPointer(this->a_normal, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(this->a_normal);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iaBuffer);
}

void PObject::loadShaderVariables()
{
	this->u_PMatrix = glGetUniformLocation(this->faceProgram, "projection");
	this->u_VMatrix = glGetUniformLocation(this->faceProgram, "view");
	this->u_MMatrix = glGetUniformLocation(this->faceProgram, "model");
	this->u_CameraPos = glGetUniformLocation(this->atmoProgram, "cameraPos");
	this->f_lambda = glGetUniformLocation(this->atmoProgram, "wavelength");

	this->a_position = glGetAttribLocation(this->faceProgram, "position");
	this->a_normal = glGetAttribLocation(this->faceProgram, "normal");
	this->a_color = glGetAttribLocation(this->faceProgram, "color");
}

void PObject::loadShader(GLuint& shaderProgram, string shaderName)
{
	shaderProgram = glCreateProgram();
	if (shaderProgram == -1)
	{
		fprintf(stderr, "Error creating program");
	}

	ifstream inv("./Source/Shaders/" + shaderName + ".vert");
	string v((istreambuf_iterator<char>(inv)), istreambuf_iterator<char>());

	ifstream inf("./Source/Shaders/" + shaderName + ".frag");
	string f((istreambuf_iterator<char>(inf)), istreambuf_iterator<char>());

	GLuint v_obj = glCreateShader(GL_VERTEX_SHADER);
	GLuint f_obj = glCreateShader(GL_FRAGMENT_SHADER);

	this->createShader(shaderProgram, v.c_str(), v_obj);
	this->createShader(shaderProgram, f.c_str(), f_obj);

	GLint success = 0;
	GLchar errLog[1024] = { 0 };

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shaderProgram, sizeof(errLog), NULL, errLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errLog);
		//exit(1);
	}
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(errLog), NULL, errLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", errLog);
		//exit(1);
	}

	glDetachShader(shaderProgram, v_obj);
	glDetachShader(shaderProgram, f_obj);
}

void PObject::createShader(GLuint& shaderProgram, const char* shadertext, GLuint& s_obj)
{
	const GLchar* p[1];
	p[0] = shadertext;
	GLint lengths[1];
	lengths[0] = strlen(shadertext);
	glShaderSource(s_obj, 1, p, lengths);
	glCompileShader(s_obj);
	GLint success;
	glGetShaderiv(s_obj, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		cout << "error compiling shader" << endl;
		//exit(1);
	}
	glAttachShader(shaderProgram, s_obj);
}

PlanetMesh PObject::getMesh()
{
	return this->mesh;
}