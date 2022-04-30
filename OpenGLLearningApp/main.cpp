/*
* ref : https://programmerah.com/drawing-a-cube-with-opengl-17925/
For Projection, View Matrices
Cube object/model Positions
*/
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <cmath>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "RotationalMechanics.h"
#include "Coordinates3D.h"
using namespace std;

const GLint WIDTH = 1200, HEIGHT = 900;
const float xMovementMaxLimit = 5.0f;
const float incrementalOffset = 0.0005f;
float alpha = 0.0f; // angular acceleration
Coordinates3D centre;
float omega0 = 0.0f;
float theta0 = 0.0f;
RotationalMechanics* rotationalMechanics;
bool direction = true;
float lastFrame = 0.0f;
float deltaTime = 0.0f;
//creating indentifiers for VAO, VBO and shaders
GLuint shader, VAO, VBO, modelMatrix, mvpMatrix;  // VAO holds VBOs

static const char* vShader = " \n\
#version 330				\n\
							\n\
layout (location = 0) in  vec3 pos;						\n\
														\n\
uniform mat4 modelMatrix;														\n\
														\n\
void main()	\n\
{									\n\
    gl_Position = modelMatrix * vec4(0.4 * pos.x,0.4 * pos.y,0.4 * pos.z , 1.0);										\n\
}									\n\
";

static const char* fShader = "\n\
#version 330						\n\
										\n\
out vec4 colour;									\n\
										\n\
void main()										\n\
{											\n\
	colour = vec4(0.0, 0.0, 1.0, 1.0);		\n\
}"; 

void CreateTriangle()
{
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, //triangle 1 : begin
		-1.0f,-1.0f,1.0f,
		-1.0f,1.0f,1.0f,  //triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void AddShaders(GLint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theShaderCode[1];
	theShaderCode[0] = shaderCode;

	GLint theCodeSize[1];
	theCodeSize[0] = strlen(shaderCode);
	

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glShaderSource(theShader, 1, theShaderCode, theCodeSize);
	glCompileShader(theShader);


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();
	
	if (!shader)
	{
		cout << "error creating shaders Program" << endl;
		return;
	}

	AddShaders(shader, vShader, GL_VERTEX_SHADER);
	AddShaders(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "error linking Program" << eLog;
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "error validating Program" << eLog;
		return;
	}
	modelMatrix = glGetUniformLocation(shader, "modelMatrix");
	mvpMatrix = glGetUniformLocation(shader, "mvpMatrix");
}

void processFrame()
{
	float thisFrame = glfwGetTime();
	deltaTime = thisFrame - lastFrame;
	lastFrame = thisFrame;
}

/*
	Technically This function allows us to define physical quantities
	such as Mass m, Angle of Torque pHI, lever l, Magnitude of Force   
*/
float computedConstantAngularAcceleration()
{
	// Compute torque
	float torque = rotationalMechanics->calculatingTorque(2.0f, 6.0f, 90.0f);
	
	// Moment of Interia 
	float momentOfInertia = rotationalMechanics->momentOfInertia(25.0f, 2.0f);
	return rotationalMechanics->computeConstantAngularAcceleration(momentOfInertia, torque);
}

Coordinates3D nextCoordinatePositionAroundCircularPath(float deltaTime)
{
	const float omega = rotationalMechanics->computeAngularVelocity(omega0,alpha,deltaTime);
	const float theta = rotationalMechanics->computeAngularDisplacement(theta0, omega0,alpha, deltaTime);
	const Coordinates3D nextPositionalCoordinates = rotationalMechanics->computeNextObjectPositionAlongCircularPath(theta0, 15.0f,centre);
	omega0 = omega;
	theta0 = theta;
	return nextPositionalCoordinates;
}

void applyObjectTransform(Coordinates3D nextObjectPosition)
{
	glm::mat4 modelTranslateMatrix(1.0f); // declaring an identity matrix
	// Projection matrix to transform --  45� View, 4:3 , display range : 0.1 unit to 100 units
	glm::mat4 Projection = glm::perspective(-45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(35, 3, -3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)		
	);


	modelTranslateMatrix = glm::translate(modelTranslateMatrix, glm::vec3(nextObjectPosition.x, 0.0f, nextObjectPosition.y));
	glm::mat4 modelTransformMatrix(1.0f);
	modelTransformMatrix = Projection * View * modelTranslateMatrix;
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(modelTransformMatrix));
}

int main()
{
	alpha = computedConstantAngularAcceleration();
	rotationalMechanics = new RotationalMechanics();
	centre.x = 0.0f;
	centre.y = 0.0f;
	if (!glfwInit())
	{
		std::cout << "glfw failed to initialize!";
		glfwTerminate();
		return 1;
	}
	
	//Set GLFW Windows Properties 
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// No backward compatibility
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allowing foward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* renderWindow = glfwCreateWindow(WIDTH, HEIGHT,"Sample Scene", nullptr, nullptr);
	if (!renderWindow)
	{
		std::cout << "glfw failed to create Window!";
		glfwTerminate();
		return 1;
	}

	// retrieving buffer size information
	int bufferHeight, bufferWidth;
	glfwGetFramebufferSize(renderWindow, &bufferWidth, &bufferHeight);
	
	//set context for GLEW to use
	glfwMakeContextCurrent(renderWindow);

	//Allow latest extensive OpenGL features
	glewExperimental = GL_TRUE;
	
	if (glewInit()!= GLEW_OK)
	{
		std::cout << "glew failed to intialize";
		glfwDestroyWindow(renderWindow);
		glfwTerminate();
		return 1;
	}

	// Set Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	
	CreateTriangle();
	CompileShaders();

	//game looping 
	while (!glfwWindowShouldClose(renderWindow))
	{
		//process Frame
		processFrame();
		// Get + Handle Window Input
		glfwPollEvents();
		
		// Clear Window 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shader);
		Coordinates3D nextObjectPosition = nextCoordinatePositionAroundCircularPath(deltaTime);
		applyObjectTransform(nextObjectPosition); // -1.0f represent the downward direction in openGL coordinate representational system
		glBindVertexArray(VAO); 
		glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(renderWindow); 
	}
	return 0;
}

