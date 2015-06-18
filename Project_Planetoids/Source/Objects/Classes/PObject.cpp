#include "../Headers/PObject.h"


PObject::PObject(string name, GLfloat radius)
{
	this->setName(name);
	this->setRadius(radius);
	this->mesh = new PlanetMesh(radius, 5);
	this->modelMatrix = glm::mat4(1.0f);
	this->setLoc(glm::vec3(0.f, 0.f, 0.f));
	//this->loc = glm::vec3(0.f, 0.f, -200.f);

	this->loadShader(this->faceProgram, "shadertest");
	this->loadShader(this->edgeProgram, "shadertest2");
	this->loadShaderVariables();
	this->bufferObjects();
}


PObject::~PObject()
{
	glDeleteProgram(this->faceProgram);
	glDeleteProgram(this->edgeProgram);
}

void PObject::setName(string name)
{
	this->name = name;
}

void PObject::setRadius(GLfloat radius)
{
	this->radius = radius;
}

void PObject::update()
{
	//glm::translate(this->modelMatrix, this->loc);
	this->modelMatrix = glm::translate(glm::mat4(1.f), this->loc) * glm::rotate(glm::mat4(1.f), (float)glfwGetTime()*.5f, glm::vec3(0.f, 1.f, 0.f));
}

void PObject::draw(Camera* camera)
{
	glUniformMatrix4fv(u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glUseProgram(this->edgeProgram);
	glDepthRange(0.0, 0.99999);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	this->bindBuffers(0);
	glDrawElements(GL_QUADS, this->mesh->getNumInd(), GL_UNSIGNED_INT, 0);

	glUniformMatrix4fv(u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(u_MMatrix, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glUseProgram(this->faceProgram);
	glDepthRange(0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	this->bindBuffers(0);
	glDrawElements(GL_QUADS, this->mesh->getNumInd(), GL_UNSIGNED_INT, 0);
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

void PObject::bufferObjects()
{
	glGenBuffers(1, &this->vBuffer);
	glGenBuffers(1, &this->cBuffer);
	glGenBuffers(1, &this->nBuffer);
	glGenBuffers(1, &this->iBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->mesh->getVerts().size() * 3), &this->mesh->getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->cBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->mesh->getVerts().size() * 3), &this->mesh->getColors()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->nBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(this->mesh->getVerts().size() * 3), &this->mesh->getNormals()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->iBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*this->mesh->getNumInd(), &this->mesh->getIndices()[0], GL_STATIC_DRAW);
}

void PObject::bindBuffers(int wireframe)
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

void PObject::loadShaderVariables()
{
	this->u_PMatrix = glGetUniformLocation(this->faceProgram, "projection");
	this->u_VMatrix = glGetUniformLocation(this->faceProgram, "view");
	this->u_MMatrix = glGetUniformLocation(this->faceProgram, "model");

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

PlanetMesh* PObject::getMesh()
{
	return this->mesh;
}