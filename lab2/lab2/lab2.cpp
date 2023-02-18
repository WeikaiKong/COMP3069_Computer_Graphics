#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"
#include "shader.h"

float vertices[] =
{
	//pos					//col					
	0.5f, 0.5f, 0.f,		1.f, 0.f, 0.f,
	-0.5f, 0.5f, 0.f,		0.f, 1.f, 0.f,
	-0.f,  -0.5f, 0.f,		0.f, 0.f, 1.f
};

float move_x = 0.f;
float move_y = 0.f;

 
void processInput(GLFWwindow* window)
{
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{	
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)		move_y += 0.01;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)	move_y -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)	move_x -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)	move_x += 0.01;
}

unsigned int loadShaderSource()
{

	return 0;
}

int main(int argc, char** argv)
{	
	// window API
	GLFWwindow* window = CeateWindow(800, 600, "A triangle");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// shader API
	int shaderProgram = LoadShader("triangle.vert", "flat.frag");

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 6 float: first attribuate (pos) is 3 floats, and starts 0 floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// second attribuate (color) is 3 floats, and starts 3 floats
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//




	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram(shaderProgram);
		//int ms = (int)(glfwGetTime() * 1000.f);
		//float col_com = (float)(ms%1000)/1000.f;
		// find the uniform varaiables in the shader program
		//int loc = glGetUniformLocation(shaderProgram, "grey_level");
		//glUniform1f(loc, col_com);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

