#include "Mesh.h"

#include "GL/glew.h"

Mesh::Mesh(std::vector<Vertex> VertexData, std::vector<unsigned int> IndexData)
{
	Indices = IndexData;
	Vertices = VertexData;
	InitializeGLObjects();
}


Mesh::Mesh(std::vector<Vertex> VertexData)
{
	Vertices = VertexData;
	for (unsigned int i = 0; i < Vertices.size(); i++) {
		Indices.push_back(i);
	}
	InitializeGLObjects();
}

void Mesh::InitializeGLObjects()
{
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

	//create IBO
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

	//shader layouts
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), ((char*)(sizeof(glm::vec3))));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), ((char*)(2 * sizeof(glm::vec3))));
	glEnableVertexAttribArray(2);
}

void Mesh::Bind()
{
	glBindVertexArray(VAO);
}

Mesh::~Mesh()
{
	glBindVertexArray(0);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}