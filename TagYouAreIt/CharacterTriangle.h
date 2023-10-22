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
	glm::vec3 GetPointB() { return m_pointB; }
	glm::vec3 GetPointC() { return m_pointC; }
	CharacterType GetCharacterType() { return m_characterType; }
	glm::vec4 GetColor() { return m_color; }
	void SetColor(glm::vec4 _color) { m_color = _color; }
	void SetColorRGBA(float _r, float _g, float _b, float _a) { m_color = glm::vec4(_r, _g, _b, _a); }
	void SetCharacterType(CharacterType _characterType) { m_characterType = _characterType; }
	//bool GetTagged() { return m_tagged; }

	static const glm::vec3 UNIT_VECTOR_A;
	static const glm::vec3 UNIT_VECTOR_B;
	static const glm::vec3 UNIT_VECTOR_C;

	static const glm::vec4 RGBA_PLAYER;
	static const glm::vec4 RGBA_NOT_TAGGED;
	static const glm::vec4 RGBA_TAGGED;
private:
	glm::vec3 m_position;
	glm::vec3 m_pointA;
	glm::vec3 m_pointB;
	glm::vec3 m_pointC;
	CharacterType m_characterType;
	glm::vec4 m_color;
	//bool m_tagged;
};

#endif // RESOLUTION_H
