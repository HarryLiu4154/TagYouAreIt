//#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Singleton.h"
#include "Shader.h"
#include "Mesh.h"
#include "WindowController.h"
#include "Camera.h"
#include "CharacterTriangle.h"

class GameController : public Singleton<GameController>
{
public:
	// Constructors / Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void Initialize();
	void RunGame();

private:
	Shader m_shader;
	Camera m_camera;
	Mesh m_mesh;

	std::vector<CharacterTriangle> m_characters;
	vector<GLfloat> SetMeshVertexData();
};

#endif // !GAME_CONTROLLER_H