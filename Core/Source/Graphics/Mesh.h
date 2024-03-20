#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
};

class Mesh
{

public:

	std::vector<unsigned int> Indices;
	std::vector<Vertex> Vertices;

	Mesh(std::vector<Vertex> VertexData, std::vector<unsigned int> IndexData);
	Mesh(std::vector<Vertex> vertexData);
	void Bind();
	~Mesh();

private:
	unsigned int VAO, VBO, IBO;
	inline void InitializeGLObjects();
};

