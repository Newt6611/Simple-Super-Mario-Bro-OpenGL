#pragma once

#include "GL/glew.h"
#include "Renderer2D.h"
#include "glm/glm.hpp"
#include "box2d/box2d.h"
#include "Input.h"

#include <string>

class IObject
{
public:
	virtual void OnUpdate(float ts) = 0;
	virtual void OnRender() = 0;
	virtual void OnTriggerEnter(IObject* collider) = 0;

	inline glm::vec2 GetPosition() const { return m_Position; }
	inline float GetRotation() const { return m_Rotation; }
	inline glm::vec2 GetScale() const { return m_Scale; }

public:
	std::string tag = "default";

protected:
	glm::vec2 m_Position;
	float m_Rotation;
	glm::vec2 m_Scale;

};