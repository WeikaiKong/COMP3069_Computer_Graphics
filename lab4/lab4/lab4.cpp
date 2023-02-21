#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>


#include "shader.h"
#include "window.h"

#include <iostream>


float vertices0[] =
{
	//pos							col
	0.f, 0.25f, 0.f,  				1.f, 0.f, 0.f,	//t
	-0.25f, -0.25f, 0.f,  			1.f, 0.f, 0.f,	//bl
	0.25f,  -0.25f, 0.f,  			1.f, 0.f, 0.f	//br
};

float vertices1[] =
{
	//pos							col
	0.f, 0.25f, 0.f,  				0.f, 1.f, 0.f,	//t
	-0.25f, -0.25f, 0.f,  			0.f, 1.f, 0.f,	//bl
	0.25f,  -0.25f, 0.f,  			0.f, 1.f, 0.f	//br
};


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char** argv)
{
	GLFWwindow* window = CreateWindow(800, 600, "2D Transformations");


	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);



	unsigned int shader_program = LoadShader("simple.vert", "simple.frag");

	//create VAO and VBO
	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);
	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	//model #1
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//model #2
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//

	glUseProgram(shader_program);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// model #1
		//create a 4x4 matrix to store the variable M0: transformation matrix
		glm::mat4 M0 = glm::mat4(1.f);
		// translation using a transformation matrix: red moves to the right 0.5
		M0 = glm::translate(M0, glm::vec3(.5, 0.f, 0.f));
		// rotation using a transformation matrix: red rotates in 90 degree
		M0 = glm::rotate(M0, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
		// scale using a transformation matrix: scale in x dimention 
		M0 = glm::scale(M0, glm::vec3(2.f, 1.f, 1.f));
		//get the location of the uniform
		int loc = glGetUniformLocation(shader_program, "transformation");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(M0));
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//model #2
		//create a 4x4 matrix to store the variable M1: transformation matrix
		glm::mat4 M1 = glm::mat4(1.f);
		// translation using a transformation matrix: green moves to the up 0.5
		M1 = glm::translate(M1, glm::vec3(0.f, .5f, 0.f));
		// rotation using a transformation matrix: red rotates in -90 degree
		M1 = glm::rotate(M1, glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));
		// scale using a transformation matrix: scale in y dimention 
		M1 = glm::scale(M1, glm::vec3(1.f, 2.f, 1.f));
		//get the location of the uniform
		loc = glGetUniformLocation(shader_program, "transformation");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(M1));
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

