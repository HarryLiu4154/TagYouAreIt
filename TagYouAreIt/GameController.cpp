#include "GameController.h"
#include "WindowController.h"

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

	m_characters.push_back(CharacterTriangle(glm::vec3(0.0f, 0.0f, 0.0f), CharacterType::PLAYER));
}

vector<GLfloat> GameController::SetMeshVertexData() 
{
	vector<GLfloat> newVertexData = {};
	for (auto& character : m_characters) {
		newVertexData.insert(newVertexData.end(), {
				character.GetPointA().x,
				character.GetPointA().y,
				character.GetPointA().z,
				character.GetColor().x,
				character.GetColor().y,
				character.GetColor().z,
				character.GetColor().w,

				character.GetPointB().x,
				character.GetPointB().y,
				character.GetPointB().z,
				character.GetColor().x,
				character.GetColor().y,
				character.GetColor().z,
				character.GetColor().w,

				character.GetPointC().x,
				character.GetPointC().y,
				character.GetPointC().z,
				character.GetColor().x,
				character.GetColor().y,
				character.GetColor().z,
				character.GetColor().w,
			}
		);
	}

	return newVertexData;
	//m_mesh.SetVertexData(newVertexData);
}

void GameController::RunGame()
{
	// Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();

	// Create and compile our GLSL program from the shaders
	m_shader = Shader();
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = Mesh();
	m_mesh.Create(&m_shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do {
		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		//SetMeshVertexData(&m_mesh);
		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView(), SetMeshVertexData());
		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);
	// While escape is not pressed and window has not closed

	m_mesh.Cleanup();
	m_shader.CleanUp();
}