#include "./Headers/Planetoids.h"
#include "./Mesh/Headers/PlanetMesh.h"

#define SUB_LVL 7
#define planet 0

void init(GLFWwindow* window);
void draw(GLFWwindow* window);
void update();

void initShaders(GLuint s_program);
void createShader(GLuint s_program, const char* shaderText, GLenum s_type);
void loadShader(GLuint s_program, string shaderName, GLenum s_type);

PlanetMesh* rect;
PlanetMesh::side* side;
Camera camera;

bool wireframe = false;
GLfloat r = 10.f;

GLfloat colors[] =
{ 1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f };

vector<GLfloat> colors2;
vector<GLfloat> normals2;

GLfloat normals[] = {
	-1.f, 1.f, 1.f,
	1.f, 1.f, 1.f,
	1.f, -1.f, 1.f,
	-1.f, -1.f, 1.f,
	-1.f, 1.f, -1.f,
	1.f, 1.f, -1.f,
	1.f, -1.f, -1.f,
	-1.f, -1.f, -1.f
};

GLuint u_PMatrix;
GLuint u_VMatrix;
GLuint u_MMatrix;

GLuint a_position;
GLuint a_normal;
GLuint a_color;

GLuint shaderProgram;

// Buffers
GLuint vBuffer;
GLuint cBuffer;
GLuint nBuffer;
GLuint iBuffer;

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
}

int main(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Planetoids", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetKeyCallback(window, key_callback);
	glewInit();
	
	shaderProgram = glCreateProgram();

	init(window);
	while (!glfwWindowShouldClose(window))
	{
		draw(window);
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void initBuffers()
{
	glGenBuffers(1, &vBuffer);
	glGenBuffers(1, &cBuffer);
	glGenBuffers(1, &nBuffer);
	glGenBuffers(1, &iBuffer);
}

void bindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(rect->getVerts().size()*3), &rect->getLocations()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, cBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(rect->getVerts().size()*3), &rect->getColors()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, nBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*(rect->getVerts().size()*3), &rect->getNormals()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, iBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*rect->getNumInd(), &rect->getIndices()[0], GL_STATIC_DRAW);
}

void init(GLFWwindow* window)
{
	glm::vec3 pos(0.f, 0.f, 20.f);
	glm::vec3 tar(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	camera = Camera(pos, tar, up);
	rect = new PlanetMesh(10.0f, SUB_LVL);

	colors2.resize(rect->getVerts().size() * 3, 1.0f);
	normals2.resize(rect->getVerts().size() * 3, 1.0f);
	
	initShaders(shaderProgram);
	
	u_PMatrix = glGetUniformLocation(shaderProgram, "projection");
	u_VMatrix = glGetUniformLocation(shaderProgram, "view");
	u_MMatrix = glGetUniformLocation(shaderProgram, "model");

	a_position = glGetAttribLocation(shaderProgram, "position");
	a_normal = glGetAttribLocation(shaderProgram, "normal");
	a_color = glGetAttribLocation(shaderProgram, "color");
	  
	initBuffers();
	bindBuffers();

	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	//gluPerspective(30, width / height, 0, 30);
}

void bindings()
{
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(a_position);

	glBindBuffer(GL_ARRAY_BUFFER, cBuffer);
	glVertexAttribPointer(a_color, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(a_color);

	glBindBuffer(GL_ARRAY_BUFFER, nBuffer);
	glVertexAttribPointer(a_normal, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(a_normal);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
}

void draw(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime()*1.f, glm::vec3(0.f, 1.f, 0.f));

	bindings();
	
	glUniformMatrix4fv(u_PMatrix, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(u_VMatrix, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	glUniformMatrix4fv(u_MMatrix, 1, GL_FALSE, glm::value_ptr(model));
	
	glDrawElements(GL_QUADS, rect->getNumInd(), GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

//Shaders-------------------------------------------------------------------------------
void createShader(GLuint s_program, const char* shaderText, GLenum s_type)
{
	GLuint s_obj = glCreateShader(s_type);

	const GLchar* p[1];
	p[0] = shaderText;
	GLint lengths[1];
	lengths[0] = strlen(shaderText);
	glShaderSource(s_obj, 1, p, lengths);
	glCompileShader(s_obj);
	GLint success;
	glGetShaderiv(s_obj, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		cout << "error compiling shader" << endl;
		//exit(1);
	}
	glAttachShader(s_program, s_obj);
}

void loadShader(GLuint s_program, string shaderFile, GLenum s_type)
{
	ifstream in("./Source/Shaders/" + shaderFile);
	string v((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	createShader(s_program, v.c_str(), s_type);
}

void initShaders(GLuint s_program)
{
	
	loadShader(shaderProgram, "shadertest.vert", GL_VERTEX_SHADER);
	loadShader(shaderProgram, "shadertest.frag", GL_FRAGMENT_SHADER);

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

	glUseProgram(shaderProgram);
}
//Shaders-------------------------------------------------------------------------------