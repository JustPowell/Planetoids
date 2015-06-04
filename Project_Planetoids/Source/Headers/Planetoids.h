#pragma once

//#define GLFW_INCLUDE_GLEXT
//#define GLFW_INCLUDE_GLU

#include <GL\glew.h>
#include <glfw3.h>
#include <GL\GLU.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<GLfloat, GLfloat, GLfloat> vector3f;
typedef tuple<GLfloat, GLfloat, GLfloat> color3f;
typedef tuple<GLfloat, GLfloat, GLfloat> normal3f;
typedef tuple<int, int, int> tup3i;