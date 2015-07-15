#pragma once

#include "../../Headers/Planetoids.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void loadShader(GLuint& shaderProgram, string shaderName);
	void createShader(GLuint& shaderProgram, const char* shadertext, GLuint& s_obj);
	void reloadShader(string program);
	void deleteShader(string program);

	void createProgram(string program);
	GLuint getProgram(string program);

private:
	unordered_map<string, GLuint> programMap;
};

