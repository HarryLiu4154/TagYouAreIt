#ifndef CHARACTERTRIANGLE_H
#define CHARACTERTRIANGLE_H

#include "StandardIncludes.h"
#include <cmath>

enum CharacterType { PLAYER, NOT_TAGGED, TAGGED };

class CharacterTriangle
{
public:
	CharacterTriangle(glm::vec3 _position, CharacterType _characterType);
	virtual ~CharacterTriangle();
	
	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 GetPointA() { return m_pointA; }
	void SetPointA(glm::vec3 _pointA) { m_pointA = _pointA; }
	glm::vec3 GetPointB() { return m_pointB; }
	void SetPointB(glm::vec3 _pointB) { m_pointB = _pointB; }
	glm::vec3 GetPointC() { return m_pointC; }
	void SetPointC(glm::vec3 _pointC) { m_pointC = _pointC; }
	CharacterType GetCharacterType() { return m_characterType; }
	void SetCharacterType(CharacterType _characterType) { m_characterType = _characterType; }

	void MoveX(float _x_delta);
	void MoveY(float _y_delta);

	static const glm::vec3 UNIT_VECTOR_A;
	static const glm::vec3 UNIT_VECTOR_B;
	static const glm::vec3 UNIT_VECTOR_C;

private:
	glm::vec3 m_position;
	glm::vec3 m_pointA;
	glm::vec3 m_pointB;
	glm::vec3 m_pointC;
	CharacterType m_characterType;
};

#endif // RESOLUTION_H
