#define _USE_MATH_DEFINES 
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "shader.h"
#include "window.h"

#include <iostream>



void processInput(GLFWwindow* window)
{
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}




#define DEG2RAD(n)	n*(M_PI/180)

//DEFINE CreateCircle() here
float* CreateCircle(int num_segments, float radius)
{
	int n_verts = num_segments * 3;
	int n_atts = n_verts * 3;
	float* verts = (float*)malloc(sizeof(float) * (n_atts));

	float angle_offset = DEG2RAD(360.f) / num_segments;
	float current_angle = 0.f;

	for (int sc = 0; sc < num_segments; sc++)
	{
		verts[sc * 3 * 3 + 0] = 0.f;
		verts[sc * 3 * 3 + 1] = 0.f;
		verts[sc * 3 * 3 + 2] = 0.f;

		verts[sc * 3 * 3 + 3] = sin(current_angle) * radius;
		verts[sc * 3 * 3 + 4] = cos(current_angle) * radius;
		verts[sc * 3 * 3 + 5] = 0.f;

		verts[sc * 3 * 3 + 6] = sin(current_angle + angle_offset) * radius;
		verts[sc * 3 * 3 + 7] = cos(current_angle + angle_offset) * radius;
		verts[sc * 3 * 3 + 8] = 0.f;

		current_angle += angle_offset;
	}

	return verts;
}


int main(int argc, char** argv)
{
	//MAKE A WINDOW HERE
	GLFWwindow* window = CeateWindow(800, 600, "modeling");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//LOAD THE SHADERS HERE
	int shaderProgram = LoadShader("triangle.vert", "flat.frag");

	//CREATE CIRCLE HERE
	int num_segs = 32;
	float* vertices = CreateCircle(num_segs, .5f);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_segs * 3 * 3, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//FREE THE ALLOCATED MEMORY HERE
	free(vertices);

	glfwTerminate();

	return 0;
}

