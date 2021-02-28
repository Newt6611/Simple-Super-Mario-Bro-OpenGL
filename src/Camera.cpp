#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top)
{
	m_Position = glm::vec2(0);
	m_Projection = glm::ortho(left, right, bottom, top , -1.f, 1.f);
	m_ViewMatrix = glm::mat4(1);
}

void Camera::ReCaculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0.f } );

	transform = glm::inverse(transform);

	m_ViewMatrix = transform;
}
