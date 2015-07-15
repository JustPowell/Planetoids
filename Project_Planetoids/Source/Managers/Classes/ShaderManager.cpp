#include "../Headers/ShaderManager.h"


ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
	for (auto it = this->programMap.begin(); it != this->programMap.end(); it++)
	{
		glDeleteShader(this->programMap[it->first]);
	}
}

void ShaderManager::createShader(GLuint& shaderProgram, const char* shadertext, GLuint& s_obj)
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

void ShaderManager::loadShader(GLuint& shaderProgram, string shaderName)
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

	createShader(shaderProgram, v.c_str(), v_obj);
	createShader(shaderProgram, f.c_str(), f_obj);

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

void ShaderManager::reloadShader(string program)
{
	if (this->programMap.find(program) != this->programMap.end())
	{
		glDeleteShader(this->programMap[program]);
		GLuint p;
		this->loadShader(p, program);
		this->programMap[program] = p;
	}
}

void ShaderManager::deleteShader(string program)
{
	if (this->programMap.find(program) != this->programMap.end())
	{
		glDeleteShader(this->programMap[program]);
		this->programMap[program] = -1;
	}
}

void ShaderManager::createProgram(string program)
{
	if (this->programMap.find(program) == this->programMap.end())
	{
		GLuint p;
		this->loadShader(p, program);
		this->programMap[program] = p;
	}
}

GLuint ShaderManager::getProgram(string program)
{
	if (this->programMap.find(program) != this->programMap.end()){
		return this->programMap[program];
	}
	
}