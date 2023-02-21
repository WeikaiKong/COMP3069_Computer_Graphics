#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "window.h"






float vertices[] =
{
	//pos					//col			
	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  	1.f, 0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 0.0f,

	-1.0f, -1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	1.0f, -1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	-1.0f,  1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,
	-1.0f, -1.0f,  1.0f,  	0.0f, 1.0f, 0.0f,

	-1.0f,  1.0f,  1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, -1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f,  1.0f,  1.0f,  	0.0f, 0.0f, 1.0f,

	1.0f,  1.0f,  1.0f,  	1.f, 1.0f, 0.0f,
	1.0f,  1.0f, -1.0f,  	1.f, 1.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 	1.f, 1.0f, 0.0f,
	1.0f, -1.0f, -1.0f,  	1.f, 1.0f, 0.0f,
	1.0f, -1.0f,  1.0f,  	1.f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f,  	1.f, 1.0f, 0.0f,

	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 1.0f,
	1.0f, -1.0f,  1.0f,  	1.f, 0.0f, 1.0f,
	1.0f, -1.0f,  1.0f,  	1.f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,  	1.f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  	1.f, 0.0f, 1.0f,

	-1.0f,  1.0f, -1.0f,  	0.0f, 1.f, 1.0f,
	1.0f,  1.0f, -1.0f,  	0.0f, 1.f, 1.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.f, 1.0f,
	1.0f,  1.0f,  1.0f,  	0.0f, 1.f, 1.0f,
	-1.0f,  1.0f,  1.0f,  	0.0f, 1.f, 1.0f,
	-1.0f,  1.0f, -1.0f, 	0.0f, 1.f, 1.0f,
};

float vertices2[] =
{
	//BASE
	//pos					//col			
	-1.0f, -1.0f, 1.0f,  	1.f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,  	1.f, 1.0f, 1.0f,
	1.0f,  -1.0f, -1.0f,  	1.f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,  	1.f, 1.0f, 1.0f,
	1.0f,  -1.0f, -1.0f,  	1.f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,  	1.f, 1.0f, 1.0f,

	//TL
	//pos					//col			
	.25f, -1.0f, .25f,  		1.f, 0.0f, 0.0f,
	0.5f,  -.75f,  0.5f,  	1.0f, 0.0f, 0.0f,
	.25f,  -1.0f, .75f,  	1.f, 0.0f, 0.0f,

	//TB
	//pos					//col			
	.75f,  -1.0f, .25f,  	1.f, 0.0f, 0.0f,
	0.5f,  -.75f,  0.5f,  	1.0f, 0.0f, 0.0f,
	.25f, -1.0f, .25f,  		1.f, 0.0f, 0.0f,

	//TR
	//pos					//col			
	.75f, -1.0f,  .75f,  	1.0f, 0.0f, 0.0f,
	0.5f,  -.75f,  0.5f,  	1.0f, 0.0f, 0.0f,
	.75f,  -1.0f,  .25f,  	1.0f, 0.0f, 0.0f,

	//TF
	//pos					//col			
	.75f,  -1.0f, .75f,  	1.f, 0.0f, 0.0f,
	0.5f,  -.75f,  0.5f,  	1.0f, 0.0f, 0.0f,
	.25f, -1.0f, .75f,  		1.f, 0.0f, 0.0f,
};






void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)		glfwSetWindowShouldClose(window, true);
}


int main(int argc, char** argv)
{
	GLFWwindow* window = CreateWindow(800, 600, "Lab 6b");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	unsigned int shaderProgram = LoadShader("mvp1.vert", "uniform1.frag");






	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderProgram);


	while (!glfwWindowShouldClose(window))
	{
		processKeyboard(window);

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glm::mat4 view = glm::mat4(1.f);
		view = glm::translate(view, -glm::vec3(0.0f, 0.0f, 5.0f));
		int vloc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(vloc, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(45.f), (float)800 / (float)600, .1f, 10.f);
		int ploc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model = glm::mat4(1.f);
		// model = glm::translate(model, glm::vec3(0.f, 0.f, 0.0f));
		// rotate 180
		// model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.0f));
		model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.f, 0.f, -1.f));

		int mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 18);
		glBindVertexArray(0);

		model = glm::mat4(1.f);
		model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.0f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 18);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

