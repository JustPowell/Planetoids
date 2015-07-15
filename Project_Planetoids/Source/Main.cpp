#include "./Headers/Planetoids.h"
#include "./Mesh/Headers/PlanetMesh.h"
#include "./Objects/Headers/PObject.h"
#include "./Managers/Headers/ShaderManager.h"

#define SUB_LVL 0
#define planet 0

void init(GLFWwindow* window);
void draw(GLFWwindow* window);
void update();

PObject* planetObj;
PObject* planetObj2;
Camera* camera;
ShaderManager* sManager;

bool wireframe = false;
GLfloat r = 10.f;

int canmove = 0;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		wireframe = false;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		wireframe = true;
	}
	camera->move(key, action);
	planetObj->changeLambda(key, action, mods);
	planetObj->getSky().updateShader(key, action, mods);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if (canmove)
		//camera->move(window, xpos, ypos);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//double xpos, ypos;
		//int width, height;

		//glfwGetCursorPos(window, &xpos, &ypos);
		//glfwGetFramebufferSize(window, &width, &height);
		//glfwSetCursorPos(window, (double)width/2, (double)height/2);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		canmove = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		canmove = 0;
	}
}

int main(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window = glfwCreateWindow(1440, 900, "Planetoids", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glewInit();
	//int* blah = new int(3);
	//char* b = (char*)malloc(20);
	init(window);
	while (!glfwWindowShouldClose(window))
	{
		//draw(window, shaderProgram2, 1);
		//draw(window, shaderProgram, 0);
		camera->update();
		planetObj->update();
		//planetObj2->update();
		draw(window);
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	delete planetObj;
	//_CrtDumpMemoryLeaks();
	exit(EXIT_SUCCESS);
	
	//delete planetObj2;
	//return 0;
}

void init(GLFWwindow* window)
{
	sManager = new ShaderManager();
	//glm::vec3 pos(-120.f, 0.f, 0.f);
	int r = 6400.f;
	glm::vec3 pos(0.f, -r - 1, 0.f);
	glm::vec3 tar(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	camera = new Camera(pos, tar, up);

	planetObj = new PObject("shaderTest", r, sManager);
	//planetObj2 = new PObject("shaderTest", 100.f);
	planetObj->setLoc(glm::vec3( 0.f, 0.f, 0.f));
	//planetObj2->setLoc(glm::vec3(150.f, 0.f, 0.f));

	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
}

void draw(GLFWwindow* window)
{
	//glClearColor(0, .5, .5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	planetObj->draw(camera);
	planetObj->getSky().draw(camera);
	//planetObj2->draw(camera);

	glfwSwapBuffers(window);
	glfwPollEvents();
}