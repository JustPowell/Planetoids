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
	GLuint v_obj = -1, f_obj = -1, g_obj = -1, tc_obj = -1, te_obj = -1;

	shaderProgram = glCreateProgram();
	if (shaderProgram == -1)
	{
		fprintf(stderr, "Error creating program");
	}

	ifstream inv("./Source/Shaders/" + shaderName + ".vert");
	if (inv.is_open())
	{
		string v((istreambuf_iterator<char>(inv)), istreambuf_iterator<char>());
		v_obj = glCreateShader(GL_VERTEX_SHADER);
		createShader(shaderProgram, v.c_str(), v_obj);
	}

	ifstream intc("./Source/Shaders/" + shaderName + ".tessc");
	if (intc.is_open())
	{
		string tc((istreambuf_iterator<char>(intc)), istreambuf_iterator<char>());
		tc_obj = glCreateShader(GL_TESS_CONTROL_SHADER);
		createShader(shaderProgram, tc.c_str(), tc_obj);
	}

	ifstream inte("./Source/Shaders/" + shaderName + ".tesse");
	if (inte.is_open())
	{
		string te((istreambuf_iterator<char>(inte)), istreambuf_iterator<char>());
		te_obj = glCreateShader(GL_TESS_EVALUATION_SHADER);
		createShader(shaderProgram, te.c_str(), te_obj);
	}

	ifstream ing("./Source/Shaders/" + shaderName + ".geo");
	if (ing.is_open())
	{
		string g((istreambuf_iterator<char>(ing)), istreambuf_iterator<char>());
		g_obj = glCreateShader(GL_GEOMETRY_SHADER);
		createShader(shaderProgram, g.c_str(), g_obj);
	}

	ifstream inf("./Source/Shaders/" + shaderName + ".frag");
	if (inf.is_open())
	{
		string f((istreambuf_iterator<char>(inf)), istreambuf_iterator<char>());
		f_obj = glCreateShader(GL_FRAGMENT_SHADER);
		createShader(shaderProgram, f.c_str(), f_obj);
	}

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
	if (v_obj != -1)
		glDetachShader(shaderProgram, v_obj);
	if (tc_obj != -1)
		glDetachShader(shaderProgram, tc_obj);
	if (te_obj != -1)
		glDetachShader(shaderProgram, te_obj);
	if (g_obj != -1)
		glDetachShader(shaderProgram, g_obj);
	if (f_obj != -1)
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