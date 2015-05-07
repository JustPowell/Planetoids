#include "Planetoids.h"
#include "PlanetMesh.h"

#define DRAWTRIS 0
#define SUB_LVL 3

void init();
void draw();

PlanetMesh *rect = new PlanetMesh(10.0f, SUB_LVL);
PlanetMesh::side *side;
float x = 10.0f;
float y = 10.0f;
float z = 10.0f;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
	{
		x++;
		y++;
		z++;
	}
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
	{
		x--;
		y--;
		z--;
	}

}
int main(void)
{
	GLFWwindow* window;
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(1024, 768, "Planetoids", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	init();

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-ratio*2, ratio*2, -2.f, 2.f, -1.f, 1.f);
		gluPerspective(30, width / height, 0, 30);
		gluLookAt(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 1.f, 0.f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		glCullFace(GL_FRONT);

		if (!DRAWTRIS)
			glBegin(GL_QUADS);
		else
			glBegin(GL_TRIANGLES);
		for (int s = 0; s < 6; s++)
		{
			for (int f = 0; f < rect->getSide(s)->faceList.size(); f++)
			{
				if (!DRAWTRIS)
				{
					glColor3f(get<0>(rect->getSide(s)->faceList[f]->getColor()), get<1>(rect->getSide(s)->faceList[f]->getColor()), get<2>(rect->getSide(s)->faceList[f]->getColor()));
					for (int i = 0; i < 4; i++)
					{
						glVertex3f(get<0>(rect->getSide(s)->faceList[f]->getVertices().at(i)->getLocation()),
							get<1>(rect->getSide(s)->faceList[f]->getVertices().at(i)->getLocation()),
							get<2>(rect->getSide(s)->faceList[f]->getVertices().at(i)->getLocation()));
					}
				}

				else
				{
					//TRI0-------------------------
					tup3f vl = rect->getSide(s)->faceList[f]->getVertices().at(0)->getLocation();
					glVertex3f(get<0>(vl), get<1>(vl), get<2>(vl));

					vl = rect->getSide(s)->faceList[f]->getVertices().at(1)->getLocation();
					glVertex3f(get<0>(vl), get<1>(vl), get<2>(vl));

					vl = rect->getSide(s)->faceList[f]->getVertices().at(2)->getLocation();
					glVertex3f(get<0>(vl), get<1>(vl), get<2>(vl));
					glEnd();
					//------------------------------

					//TRI1--------------------------
					glBegin(GL_TRIANGLES);
					vl = rect->getSide(s)->faceList[f]->getVertices().at(0)->getLocation();
					glVertex3f(get<0>(vl), get<1>(vl), get<2>(vl));

					vl = rect->getSide(s)->faceList[f]->getVertices().at(2)->getLocation();
					glVertex3f(get<0>(vl), get<1>(vl), get<2>(vl));

					vl = rect->getSide(s)->faceList[f]->getVertices().at(3)->getLocation();
					glVertex3f(get<0>(vl), get<1>(vl), get<2>(vl));
					glEnd();
					//------------------------------
				}
			}
		}
		glEnd();
		/*
		for (int q = 0; q < 6; q++)
		{
			vector<Quad*> quadlist = rect->getQuad(q)->getQuadlist(SUB_LVL);

			for (int l = 0; l < quadlist.size(); l++)
			{
				glBegin(GL_QUADS);
				for (int i = 0; i < 4; i++)
				{
					glVertex3f(get<0>(quadlist[l]->getVerts()[i]->getLocation()),
						get<1>(quadlist[l]->getVerts()[i]->getLocation()),
						get<2>(quadlist[l]->getVerts()[i]->getLocation()));
				}
				glEnd();
			}
		}*/
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void init()
{

	GLfloat vertices[] = { -1.f, 1.f, 0.f,
						    1.f,  1.f, 0.f,
						    1.f, -1.f, 0.f,
						   -1.f, -1.f, 0.f };

	GLfloat colors[] = { 0.5f, 0.5f, 0.5f,
						 0.5f, 0.5f, 0.5f,
						 0.5f, 0.5f, 0.5f,
						 0.5f, 0.5f, 0.5f };

	GLubyte indices[] = { 0, 1, 2, 3 };
						  //0, 2, 3 };

	//vector<Pver> = { Pver() }

	//rect->setVertices(vertices);
	//rect->setColors(colors);
	//rect->setIndices(indices);

	//side = rect->getSide();
	//cout << get<0>(side->faceList[0]->getVertices().at(1)->getLocation()) << endl;

	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_VERTEX_ARRAY);
	
	//glColorPointer(3, GL_FLOAT, 0, rect->getColors());
	//glVertexPointer(3, GL_FLOAT, 0, rect->getVertices());

	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rect->getIndices());
}

void draw()
{
	//glDrawElements(GL_TRIANGLES, sizeof(rect->getIndices()), GL_UNSIGNED_BYTE, rect->getIndices());
}