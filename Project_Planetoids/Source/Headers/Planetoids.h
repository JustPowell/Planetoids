#pragma once

//#define GLFW_INCLUDE_GLEXT
//#define GLFW_INCLUDE_GLU

#include <GL\glew.h>
#include <glfw3.h>
#include <GL\GLU.h>

#include <stdlib.h>
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

using namespace std;

typedef tuple<int, int, int> tup3i;

typedef glm::vec3 vector3f;
typedef glm::vec3 color3f;
typedef glm::vec3 normal3f;

static glm::mat4 proj = glm::perspective(30.0f, (float)1024 / (float)768, 0.1f, 1000.f);