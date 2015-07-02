#pragma once

//#define GLFW_INCLUDE_GLEXT
//#define GLFW_INCLUDE_GLU
#define CRTDBG_MAP_ALLOC

#include <GL\glew.h>
#include <glfw3.h>
#include <GL\GLU.h>

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <direct.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <tuple>

#include "../Player/Camera.h"

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;

typedef tuple<int, int, int> tup3i;

typedef glm::vec3 vector3f;
typedef glm::vec3 color3f;
typedef glm::vec3 normal3f;

static glm::mat4 proj = glm::perspective(30.0f, (float)1024 / (float)768, 0.1f, 100000.f);