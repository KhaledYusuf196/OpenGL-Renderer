#include "Core.h"

#include <iostream>
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Math/Transform.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture.h"
#include <GL/glew.h>

#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"

namespace Core {

	void PrintHelloWorld()
	{
		std::cout << "Hello World!\n";
		std::cin.get();
	}

	void SetupDrawConfig()
	{

		glClearColor(0, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	bool InitializeGLEW()
	{
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			std::cout << "Error";
			getchar();
			return false;
		}
		std::cout << "\tUsing glew: " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		SetupDrawConfig();
		
		return true;
	}

	void ClearWindow()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	GLFWwindow* InitWindow(unsigned int Width, unsigned int Height)
	{
		/* Initialize the library */
		if (!glfwInit())
			return nullptr;

		/* Create a windowed mode window and its OpenGL context */
		GLFWwindow* window = glfwCreateWindow(Width, Height, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return nullptr;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		return window;
	}

	

	void UpdateWindow(GLFWwindow* window)
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			DrawScene();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	void TerminateGLFW()
	{
		glfwTerminate();
	}

	void DrawMesh(Mesh mesh, Transform transform, Camera camera, const Shader& shader, const Texture& texture)
	{
		shader.Use();
		mesh.Bind();
		texture.Bind();
		auto MVP = camera.GetProjectionMatrix() * transform.GetTransformMatrix();
		auto loc = glGetUniformLocation(shader.ShaderID, "u_MVP");
		if(loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(MVP));
		
		loc = glGetUniformLocation(shader.ShaderID, "u_camera_position");
		if(loc != -1) glUniform3fv(loc, 1, glm::value_ptr(camera.CameraTransform.Position));

		loc = glGetUniformLocation(shader.ShaderID, "u_model_mat");
		if(loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(transform.GetTransformMatrix()));


		loc = glGetUniformLocation(shader.ShaderID, "u_color_map");
		if(loc != -1) glUniform1i(loc, 0);
		
		glDrawElements(GL_TRIANGLES, mesh.Indices.size(), GL_UNSIGNED_INT, NULL);
	}


}
