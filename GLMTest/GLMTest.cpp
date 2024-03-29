// GLMTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

float P1_axisY = 0;

float P2_axisY = 0;

float B_axisX = 0;
float B_axisY = 0;

static bool TurnHit = false;
static bool WallHit = false;

void drawQuadsRed()
{
	glBegin(GL_QUADS);

	glColor3f(0.5, 0, 0);
	glVertex3f(-0.5, -0.2, 0);

	glVertex3f(-0.5, 0.2, 0);

	glVertex3f(-0.6, 0.2, 0);

	glVertex3f(-0.6, -0.2, 0);

	glEnd();
}

void drawQuadsBlue()
{
	glBegin(GL_QUADS);

	glColor3f(0, 0, 0.5);
	glVertex3f(0.5, -0.2, 0);

	glVertex3f(0.5, 0.2, 0);

	glVertex3f(0.6, 0.2, 0);

	glVertex3f(0.6, -0.2, 0);

	glEnd();
}


void drawBall()
{
	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0);
	glVertex3f(0.05, 0, 0);

	glVertex3f(0, 0.1, 0);

	glVertex3f(0.05, 0.2, 0);

	glVertex3f(0.1, 0.1, 0);
	glEnd();
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwTerminate();
		exit(0);
	}

}

void move_Red()
{
	if (TurnHit)
	{
		if (B_axisY >= P1_axisY)
			P1_axisY += 0.001;

		if (B_axisY <= P1_axisY)
			P1_axisY -= 0.001;

	}
}

void move_Green()
{
	if (!TurnHit)
	{
		if(B_axisY >= P2_axisY)
				P2_axisY += 0.001;
		
		if (B_axisY <= P2_axisY)
				P2_axisY -= 0.001;
		
	}
}

void move_Ball()
{
	if (!TurnHit)
	{
		B_axisX += 0.001;
		if (B_axisX > 0.4) {
			TurnHit = true;
		}
	}
	
	if (TurnHit)
	{
		B_axisX -= 0.001;
		if (B_axisX < -0.5) {
			TurnHit = false;
		}
	}
	if (!WallHit)
	{
		B_axisY += 0.001;
		if (B_axisY >= 0.8) {
			WallHit = true;
		}
	}

	if (WallHit)
	{
		B_axisY -= 0.001;
		if (B_axisY <= -1) {
			WallHit = false;
		}
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "GLEW is not working" << std::endl;
		return -1;
	}

	if (!GLEW_VERSION_2_1)
	{
		std::cout << "OpenGL2.1 does not supported." << std::endl;
		return -1;
	}

	if (GLEW_ARB_vertex_array_object) {
		std::cout << "vertex arrays is supported" << std::endl;
	}

	const GLubyte *glVersion = glGetString(GL_VERSION);
	std::cout << "Graphics driver : " << glVersion << std::endl;

	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "GLSL version : " << glslVersion << std::endl;

	glfwSetKeyCallback(window, key_callback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Render here */
		glClearColor(0.5f, 1.0f, 0.7f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glPushMatrix();

		glTranslatef(0, P1_axisY, 0);
		drawQuadsRed();

		glPopMatrix();

		glPushMatrix();

		glTranslatef(0, P2_axisY, 0);
		drawQuadsBlue();
		
		glPopMatrix();

		glPushMatrix();

		glTranslatef(B_axisX, B_axisY, 0);
		drawBall();

		glPopMatrix();
		
		move_Ball();
		move_Green();
		move_Red();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		
	
	}

	glfwTerminate();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
