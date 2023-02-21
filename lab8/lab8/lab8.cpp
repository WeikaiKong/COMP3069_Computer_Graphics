#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "window.h"
#include "ModelViewerCamera.h"

#include <iostream>

float vertices[] =
{

	//original task
	//t1				
	//pos					//tex
	-0.9f, 0.9f, 0.f,		0.0f, 1.0f,	//tl
	0.9f, 0.9f, 0.f,		1.0f, 1.0f,	//tr
	0.9f, -0.9f, 0.f,		1.0f, 0.0f,	//br
	//t2					
	//pos					//tex
	-0.9f, 0.9f, 0.f,		0.0f, 1.0f,	//tl
	0.9f,  -0.9f, 0.f,		1.0f, 0.0f,	//br
	-0.9f,  -0.9f, 0.f,		0.0f, 0.0f,	//bl


	/*
	//additonal task: upside down
	//t1
	//pos					//tex
	-0.9f, 0.9f, 0.f,		0.0f, 0.0f,	//tl
	0.9f, 0.9f, 0.f,		1.0f, 0.0f,	//tr
	0.9f, -0.9f, 0.f,		1.0f, 1.0f,	//br
	//t2
	//pos					//tex
	-0.9f, 0.9f, 0.f,		0.0f, 0.0f,	//tl
	0.9f,  -0.9f, 0.f,		1.0f, 1.0f,	//br
	-0.9f,  -0.9f, 0.f,		0.0f, 1.0f,	//bl
	*/
};


SCamera Camera;

void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

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
	GLFWwindow* window = CreateGLFWWindow(800, 600, "Textures");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	unsigned int shaderProgram = LoadShader("texture.vert", "texture.frag");

	//InitCamera(Camera, -90, 90);

	InitCamera(Camera, -45, 15);
	MoveAndOrientCamera(Camera, glm::vec3(0, 0, 0), cam_dist, 0.f, 0.f);
	/*
	const char* files[11] = {
		"mipmaps/grid1024x1024.bmp",
		"mipmaps/grid512x512.bmp",
		"mipmaps/grid256x256.bmp",
		"mipmaps/grid128x128.bmp",
		"mipmaps/grid64x64.bmp",
		"mipmaps/grid32x32.bmp",
		"mipmaps/grid16x16.bmp",
		"mipmaps/grid8x8.bmp",
		"mipmaps/grid4x4.bmp",
		"mipmaps/grid2x2.bmp",
		"mipmaps/grid1x1.bmp"
	};
	GLuint texture = setup_mipmaps(files, 11);
	*/
	GLuint texture = setup_texture("grid.bmp");

	//GLuint texture = setup_texture("jubilee.bmp");

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//





	while (!glfwWindowShouldClose(window))
	{
		processKeyboard(window);

		glClearColor(.5f, .5f, .5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glm::mat4 model = glm::mat4(1.f);
		model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));


		glm::mat4 view = glm::mat4(1.f);
		view = glm::lookAt(Camera.Position, Camera.Position + Camera.Front, Camera.Up);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(45.f), (float)800 / (float)600, .01f, 100.f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

