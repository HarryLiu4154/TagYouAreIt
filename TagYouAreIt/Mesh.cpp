#include "Mesh.h"
#include "Shader.h"
#include "CharacterTriangle.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_rotation = { 0, 0, 0 };
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;

	//m_texture = Texture();
	//m_texture.LoadTexture("../Assets/Textures/Wood.jpg");
	//m_texture2 = Texture();
	//m_texture2.LoadTexture("../Assets/Textures/Emoji.jpg");

	// 3 position, 3 rgb, 2 texture coords
	/*m_vertexData = {
		50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
		50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
		-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // top-left
	};*/
	// 3 position, 4 rgba
	/*m_vertexData = {
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		10.0f, -10.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-10.0f, -10.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};*/
	/*m_vertexData = {
		0.0f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		21.6506348f, -12.5000000f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-21.6506348f, -12.5000000f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};*/
	m_vertexData = {};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	// 3 vertices * 11 triangles
	for (int i = 0; i < m_vertexData.size() / 7; ++i) {
		m_indexData.push_back(i);
	}

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::SetVertexData(vector<GLfloat> _newVertexData) 
{
	m_vertexData.clear();
	m_vertexData.insert(m_vertexData.end(), _newVertexData.begin(), _newVertexData.end());

	m_indexData.clear();
	for (int i = 0; i < m_vertexData.size() / 7; ++i) {
		m_indexData.push_back(i);
	}
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	//m_texture.CleanUp();
	//m_texture2.CleanUp();
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramID()); // Use our shader

	// First attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3, // size (3 vertices per primitive)
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		7 * sizeof(float), // stride (8 floats per vertex definition)
		(void*)0); // offset

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(
		m_shader->GetAttrColors(), // The attribute we want to configure
		4, // size (3 vertices per primitive)
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		7 * sizeof(float), // stride (8 floats per vertex definition)
		(void*)(3 * sizeof(float)) // array buffer offset
	);

	// 3rd attribute : texCoords
	/*glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(
		m_shader->GetAttrTexCoords(), // The attribute we want to configure
		2, // size (3 vertices per primitive)
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		8 * sizeof(float), // stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float)) // array buffer offset
	); */

	// 4th attribute : WVP
	m_rotation.y += 0.000f;
	glm::mat4 transform = glm::rotate(_wvp, m_rotation.y, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &transform[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer); // Bind the index buffer
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);

	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());

	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//glVertexAttribPointer(0, 3/*size*/, GL_FLOAT/*type*/, GL_FALSE/*normalized*/, 0/*stride*/, (void*)0/*offset*/);
	// Draw the triangle
	//glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0, 3 vertices = 1 triangle
	//glDisableVertexAttribArray(0);
}