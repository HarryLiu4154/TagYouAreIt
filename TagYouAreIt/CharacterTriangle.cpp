#include "CharacterTriangle.h"

const glm::vec3 CharacterTriangle::UNIT_VECTOR_A = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 CharacterTriangle::UNIT_VECTOR_B = glm::vec3(sqrt(3.0f) / 2.0f, -1.0f / 2.0f, 0.0f);
const glm::vec3 CharacterTriangle::UNIT_VECTOR_C = glm::vec3(-sqrt(3.0f) / 2.0f, -1.0f / 2.0f, 0.0f);

//const glm::vec4 CharacterTriangle::RGBA_PLAYER = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//const glm::vec4 CharacterTriangle::RGBA_NOT_TAGGED = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
//const glm::vec4 CharacterTriangle::RGBA_TAGGED = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

CharacterTriangle::CharacterTriangle(glm::vec3 _position, CharacterType _characterType) 
{
	m_position = _position;

	m_pointA = glm::vec3(_position.x + UNIT_VECTOR_A.x * 25.0f, _position.y + UNIT_VECTOR_A.y * 25.0f, _position.z);
	m_pointB = glm::vec3(_position.x + UNIT_VECTOR_C.x * 25.0f, _position.y + UNIT_VECTOR_C.y * 25.0f, _position.z);
	m_pointC = glm::vec3(_position.x + UNIT_VECTOR_B.x * 25.0f, _position.y + UNIT_VECTOR_B.y * 25.0f, _position.z);
	
	m_characterType = _characterType;
}

CharacterTriangle::~CharacterTriangle()
{

}

void CharacterTriangle::MoveX(float _x_delta) {
	m_position.x += _x_delta;

	m_pointA.x += _x_delta;
	m_pointB.x += _x_delta;
	m_pointC.x += _x_delta;
}

void CharacterTriangle::MoveY(float _y_delta) {
	m_position.y += _y_delta;

	m_pointA.y += _y_delta;
	m_pointB.y += _y_delta;
	m_pointC.y += _y_delta;
}