#include "Camera.h"

Camera::Camera()
{
	m_projection = {  };
	m_view = {  };
}

Camera::~Camera()
{

}

Camera::Camera(Resolution _screenResolution)
{
	// Projection matrix : 45 degree Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	/*m_projection = glm::perspective(
		glm::radians(45.0f),
		(float)_screenResolution.m_width / (float)_screenResolution.m_height,
		0.1f,
		1000.0f //1000.0f
	);*/

	m_projection = glm::ortho(
		-((float)_screenResolution.m_width / 2),
		((float)_screenResolution.m_width / 2),
		-((float)_screenResolution.m_height / 2),
		((float)_screenResolution.m_height / 2),
		0.0f,
		100.0f
	);

	// Camera matrix
	m_view = glm::lookAt(
		glm::vec3(0, 0, 50), // Camera is at (), in world space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0, -1, 0 to look upside-down
	);
}