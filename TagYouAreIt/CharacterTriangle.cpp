#include "CharacterTriangle.h"

const glm::vec3 CharacterTriangle::UNIT_VECTOR_A = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 CharacterTriangle::UNIT_VECTOR_B = glm::vec3(sqrt(3.0f) / 2.0f, -1.0f / 2.0f, 0.0f);
const glm::vec3 CharacterTriangle::UNIT_VECTOR_C = glm::vec3(-sqrt(3.0f) / 2.0f, -1.0f / 2.0f, 0.0f);

const glm::vec4 CharacterTriangle::RGBA_PLAYER = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 CharacterTriangle::RGBA_NOT_TAGGED = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 CharacterTriangle::RGBA_TAGGED = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

CharacterTriangle::CharacterTriangle(glm::vec3 _position, CharacterType _characterType) 
{
	m_position = _position;

	m_pointA = glm::vec3(_position.x + UNIT_VECTOR_A.x * 25.0f, _position.y + UNIT_VECTOR_A.y * 25.0f, _position.z);
	m_pointB = glm::vec3(_position.x + UNIT_VECTOR_C.x * 25.0f, _position.y + UNIT_VECTOR_C.y * 25.0f, _position.z);
	m_pointC = glm::vec3(_position.x + UNIT_VECTOR_B.x * 25.0f, _position.y + UNIT_VECTOR_B.y * 25.0f, _position.z);
	//m_pointA = glm::vec3(0.0f, 0.0f, 0.0f);
	//m_pointB = glm::vec3(0.0f, 50.0f, 0.0f);
	//m_pointC = glm::vec3(50.0f, 0.0f, 0.0f);
	
	m_characterType = _characterType;

	switch (_characterType) {
		case PLAYER: 
			m_color = RGBA_PLAYER;
			break;
		case NOT_TAGGED:
			m_color = RGBA_NOT_TAGGED;
			break;
		default:
			m_color = RGBA_TAGGED;
			break;
	}
}

CharacterTriangle::~CharacterTriangle()
{

}