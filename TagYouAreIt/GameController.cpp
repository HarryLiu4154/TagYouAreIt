#define _USE_MATH_DEFINES

#include "GameController.h"
#include "WindowController.h"
#include <random>
#include <cmath>

const glm::vec4 GameController::RGBA_PLAYER = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 GameController::RGBA_NOT_TAGGED = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 GameController::RGBA_TAGGED = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

GameController::GameController()
{
	m_shader = {};
	m_camera = {};
	m_mesh = {};
	m_characters = {};
}

GameController::~GameController()
{
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_CULL_FACE);

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());

	m_characters.push_back(CharacterTriangle(glm::vec3(0.0f, 0.0f, 1.0f), CharacterType::PLAYER));
	AddNPCs(10);
}

void GameController::SetMeshVertexData(Mesh* _mesh) 
{
	vector<GLfloat> newVertexData = {};
	for (auto& character : m_characters) {

		glm::vec4 characterColor;
		switch (character.GetCharacterType()) {
			case PLAYER:
				characterColor = RGBA_PLAYER;
				break;
			case NOT_TAGGED:
				characterColor = RGBA_NOT_TAGGED;
				break;
			default:
				characterColor = RGBA_TAGGED;
				break;
		}

		newVertexData.insert(newVertexData.end(), {
				character.GetPointA().x,
				character.GetPointA().y,
				character.GetPointA().z,
				characterColor.x,
				characterColor.y,
				characterColor.z,
				characterColor.w,

				character.GetPointB().x,
				character.GetPointB().y,
				character.GetPointB().z,
				characterColor.x,
				characterColor.y,
				characterColor.z,
				characterColor.w,

				character.GetPointC().x,
				character.GetPointC().y,
				character.GetPointC().z,
				characterColor.x,
				characterColor.y,
				characterColor.z,
				characterColor.w,
			}
		);
	}

	//return newVertexData;
	_mesh->SetVertexData(newVertexData);
}

void GameController::DetectPlayerMovement()
{
	// remove this later to store player as separate entity for better coding practice
	if (m_characters.size() < 1) {
		return;
	}

	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	float movementSpeed = 2.0f;

	float deltaX = (float)(glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) * movementSpeed + (float)(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) * -movementSpeed;
	float deltaY = (float)(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) * movementSpeed + (float)(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) * -movementSpeed;
	
	m_characters.front().MoveX(deltaX);
	m_characters.front().MoveY(deltaY);
}

void GameController::AddNPCs(int _numberOfNPCs)
{
	// remove this later to store player as separate entity for better coding practice
	if (m_characters.size() < 1) {
		return;
	}

	std::random_device rd;
	std::uniform_real_distribution<float> dist(2.0f, 10.0f);
	std::uniform_int_distribution<int> negative(0, 1);

	float positionX;
	float positionY;
	int sign;

	for (int i = 0; i < _numberOfNPCs; ++i) {

		sign = (negative(rd) == 1) ? 1 : -1;
		positionX = 10.0f * (m_characters.front().GetPosition().x + sign * dist(rd));
		sign = (negative(rd) == 1) ? 1 : -1;
		positionY = 10.0f * (m_characters.front().GetPosition().y + sign * dist(rd));

		m_characters.push_back(CharacterTriangle(glm::vec3(positionX, positionY, 0.0f), CharacterType::NOT_TAGGED));
	}
}

void GameController::CalculateNPCMovement()
{
	// remove this later to store player as separate entity for better coding practice
	if (m_characters.size() < 1) {
		return;
	}

	// in C++ 20 and above we can use std::views::drop(1) from ranges library instead of this
	bool first = true;
	glm::vec3 playerPosition = m_characters.front().GetPosition();
	float movementSpeed = 1.0f;
	float distanceFromPlayer;
	float headAngle = 0.0f;

	for (auto& character : m_characters) {
		if (first) {
			first = !first;
			continue;
		}
		
		distanceFromPlayer = glm::distance(playerPosition, character.GetPosition());
		glm::vec3 positionToPlayer = glm::normalize(glm::vec3(
			character.GetPosition().x - playerPosition.x,
			character.GetPosition().y - playerPosition.y,
			0.0f
		));

		glm::vec3 positionToPointA = glm::normalize(glm::vec3(
			character.GetPointA().x - character.GetPosition().x,
			character.GetPointA().y - character.GetPosition().y,
			0.0f
		));

		headAngle = glm::dot(positionToPlayer, positionToPointA) - (float)M_PI_2;
		/*if (headAngle <= (float)M_PI) {
			headAngle = (float)M_PI - headAngle;
		}*/
		
		if (distanceFromPlayer < 200.0f) {
			character.MoveX(movementSpeed * positionToPlayer.x);
			character.MoveY(movementSpeed * positionToPlayer.y);

			// CHANGE THIS NUMBER FOR TAG RANGE
			if (distanceFromPlayer < 35.0f) {
				character.SetCharacterType(CharacterType::TAGGED);
			}
		}
		else if (distanceFromPlayer > 200.0f) {
			character.MoveX(-movementSpeed * positionToPlayer.x);
			character.MoveY(-movementSpeed * positionToPlayer.y);
		}

		/*character.SetPointA(glm::vec3(
			((character.GetPointA().x - character.GetPosition().x) * (float)cos(headAngle)) - ((character.GetPointA().y - character.GetPosition().y) * (float)sin(headAngle)) + character.GetPosition().x,
			((character.GetPointA().y - character.GetPosition().y) * (float)cos(headAngle)) + ((character.GetPointA().x - character.GetPosition().x) * (float)sin(headAngle)) + character.GetPosition().y,
			0.0f
		));

		character.SetPointB(glm::vec3(
			((character.GetPointB().x - character.GetPosition().x) * (float)cos(headAngle)) - ((character.GetPointB().y - character.GetPosition().y) * (float)sin(headAngle)) + character.GetPosition().x,
			((character.GetPointB().y - character.GetPosition().y) * (float)cos(headAngle)) + ((character.GetPointB().x - character.GetPosition().x) * (float)sin(headAngle)) + character.GetPosition().y,
			0.0f
		));

		character.SetPointC(glm::vec3(
			((character.GetPointC().x - character.GetPosition().x) * (float)cos(headAngle)) - ((character.GetPointC().y - character.GetPosition().y) * (float)sin(headAngle)) + character.GetPosition().x,
			((character.GetPointC().y - character.GetPosition().y) * (float)cos(headAngle)) + ((character.GetPointC().x - character.GetPosition().x) * (float)sin(headAngle)) + character.GetPosition().y,
			0.0f
		)); */

		/*glm::mat4 translateToOrigin = glm::translate(glm::mat4(1.0f), glm::vec3(-playerPosition.x, -playerPosition.y, -playerPosition.z));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), headAngle, glm::vec3(0, 0, 1));
		glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), playerPosition);

		glm::mat4 worldA = glm::translate(glm::mat4(1.0f), character.GetPointA());
		glm::mat4 worldB = glm::translate(glm::mat4(1.0f), character.GetPointB());
		glm::mat4 worldC = glm::translate(glm::mat4(1.0f), character.GetPointC());

		character.SetPointA(glm::vec3(glm::vec4(character.GetPointA(), 1.0f) * translateBack * rotation * translateToOrigin));
		character.SetPointB(glm::vec3(glm::vec4(character.GetPointB(), 1.0f) * translateBack * rotation * translateToOrigin));
		character.SetPointC(glm::vec3(glm::vec4(character.GetPointC(), 1.0f) * translateBack * rotation * translateToOrigin)); */
	}
}

void GameController::RunGame()
{
	// Create and compile our GLSL program from the shaders
	m_shader = Shader();
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = Mesh();
	m_mesh.Create(&m_shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do {
		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		SetMeshVertexData(&m_mesh);
		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(win); // Swap the front and back buffers

		DetectPlayerMovement();
		CalculateNPCMovement();

		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
	// While escape is not pressed and window has not closed

	m_mesh.Cleanup();
	m_shader.CleanUp();
}