//#pragma once
#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"

class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh();
	virtual ~Mesh();

	// Methods
	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp, vector<GLfloat> _newVertexData);
	void SetVertexData(vector<GLfloat> _newVertexData);

private:
	Shader* m_shader;
	GLuint m_vertexBuffer; // GPU buffer (VRAM)
	GLuint m_indexBuffer; // GPU buffer (VRAM)
	std::vector<GLfloat> m_vertexData; //  Store vertex data in RAM
	std::vector<GLubyte> m_indexData; // Store index data in RAM
	//glm::mat4 m_world;
	//glm::vec3 m_position;
	glm::vec3 m_rotation;
};

#endif // !MESH_H