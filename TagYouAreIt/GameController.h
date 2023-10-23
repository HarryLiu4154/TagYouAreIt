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

	static const glm::vec4 RGBA_PLAYER;
	static const glm::vec4 RGBA_NOT_TAGGED;
	static const glm::vec4 RGBA_TAGGED;

private:
	Shader m_shader;
	Camera m_camera;
	Mesh m_mesh;

	std::vector<CharacterTriangle> m_characters;
	void SetMeshVertexData(Mesh* mesh);
	void DetectPlayerMovement();
	void AddNPCs(int _numberOfNPCs);
	void CalculateNPCMovement();
};

#endif // !GAME_CONTROLLER_H