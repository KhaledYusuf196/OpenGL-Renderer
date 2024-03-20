#pragma once

class Texture;
class Shader;
class Camera;
class Transform;
class Mesh;
struct GLFWwindow;

namespace Core {

	void PrintHelloWorld();

	void DrawMesh(Mesh mesh, Transform transform, Camera camera, const Shader& shader, const Texture& texture);
	
	void ClearWindow();

	void DrawScene();

	GLFWwindow* InitWindow(unsigned int Width, unsigned int Height);

	void TerminateGLFW();

	bool InitializeGLEW();

	void UpdateWindow(GLFWwindow* window);

}
