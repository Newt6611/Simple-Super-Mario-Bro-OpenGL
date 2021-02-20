#pragma once

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera() {}
	Camera(float left, float right, float bottom, float top);
	
	inline void SetPosition(glm::vec2 position) { this->m_Position = position; ReCaculateViewMatrix(); }
	inline const glm::vec2& GetPosition () const { return this->m_Position; }

	inline const glm::mat4& GetViewMatrix() const { return this->m_ViewMatrix; }
	inline const glm::mat4& GetProjectionMatrix() const { return m_Projection; }

private:
	void ReCaculateViewMatrix();

private:
	glm::vec2 m_Position;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_Projection;
};