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

	float Kr = .0025f;
	float Km = .001f;
	float eSun = 30.f;
	glm::vec3 v3InvWaveLength = glm::vec3(.650, .570, .475);
	int nSamples = 4;

private:
	unordered_map<string, GLuint> programMap;
};

