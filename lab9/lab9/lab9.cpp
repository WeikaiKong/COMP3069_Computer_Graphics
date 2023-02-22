#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

#include "camera.h"
#include "ModelViewerCamera.h"
#include "shader.h"
#include "window.h"



//light direction variable here
glm::vec3 lightDirection = glm::vec3(0.1f, -.81f, -.61f);
glm::vec3 lightPos = glm::vec3(2.f, 6.f, 7.f);
SCamera Camera;


float vertices[] =
{
	//back face
	//pos					//col				//normal
	-0.5f, -0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f,  0.0f, -1.0f,

	//front face
	-0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	0.0f,  0.0f, 1.0f,

	//left face
	-0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,

	//right face
	0.5f,  0.5f,  0.5f,  	1.f, 1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f, 	1.f, 1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  	1.f, 1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  	1.f, 1.0f, 1.0f,	1.0f,  0.0f,  0.0f,

	//bottom face
	-0.5f, -0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f,  0.0f,

	//top face
	-0.5f,  0.5f, -0.5f,  	1.0f, 1.f, 1.0f,	0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  	1.0f, 1.f, 1.0f,	0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  	1.0f, 1.f, 1.0f,	0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  	1.0f, 1.f, 1.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  	1.0f, 1.f, 1.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, 	1.0f, 1.f, 1.0f,	0.0f,  1.0f,  0.0f
};








void processKeyboard(GLFWwindow* window)
{
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)		
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		lightDirection = Camera.Front;
		lightPos = Camera.Position;
	}
		

	bool cam_changed = false;
	float x = 0.f, y = 0.f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		x = 0.f;
		y = -1.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		x = 0.f;
		y = 1.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		x = -1.f;
		y = 0.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		x = 1.f;
		y = 0.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		cam_dist -= 0.1 * Camera.MovementSpeed;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		cam_dist += 0.1 * Camera.MovementSpeed;
		cam_changed = true;
	}
	if (cam_changed)
	{
		MoveAndOrientCamera(Camera, glm::vec3(0, 0, 0), cam_dist, x, y);
	}
}


int main(int argc, char** argv)
{
	GLFWwindow* window = CreateGLFWWindow(800, 600, "Lighting");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	unsigned int shaderProgram = LoadShader("phong.vert", "phong.frag");

	InitCamera(Camera, -45, 15);
	cam_dist = 5.f;
	MoveAndOrientCamera(Camera, glm::vec3(0, 0, 0), cam_dist, 0.f, 0.f);


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window))
	{

		processKeyboard(window);

		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUniform3f(glGetUniformLocation(shaderProgram, "lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightColour"), 0.f, 0.f, 1.f);
		glUniform3f(glGetUniformLocation(shaderProgram, "camPos"), Camera.Position.x, Camera.Position.y, Camera.Position.z);

		glm::mat4 view = glm::mat4(1.f);
		view = glm::lookAt(Camera.Position, Camera.Position + Camera.Front, Camera.Up);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(45.f), (float)800 / (float)600, .1f, 100.f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				for (int k = -1; k < 2; k++)
				{
					glm::mat4 model = glm::mat4(1.f);
					model = glm::translate(model, glm::vec3(float(i * 2), float(j * 2), float(k * 2)));
					glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
					glBindVertexArray(VAO);
					glDrawArrays(GL_TRIANGLES, 0, 36);

				}
			}
		}


		glBindVertexArray(0);

		glfwSwapBuffers(window);

	}

	glfwTerminate();

	return 0;
}

