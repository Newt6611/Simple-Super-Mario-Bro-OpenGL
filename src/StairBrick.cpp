#include "StairBrick.h"
#include "Game.h"

StairBrick::StairBrick(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale)
{
	game.RegisterGameEvent(*this);
	m_Position = position;
	m_Rotation = 0;
	m_Scale = scale;

	texture = &Texture::GetTexture("stair_brick");

	b2BodyDef b_def;
	b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b_def.position.Set(m_Position.x / Game::PIXEL_TO_M, m_Position.y / Game::PIXEL_TO_M);
	b_def.fixedRotation = true;
	mp_Body = physicsWorld.CreateBody(&b_def);

	b2PolygonShape b_shape;
	b_shape.SetAsBox(m_Scale.x / 2.f / Game::PIXEL_TO_M, m_Scale.y / 2.f / Game::PIXEL_TO_M);
	mp_Body->CreateFixture(&b_shape, 0.0f);
}

StairBrick::~StairBrick()
{
	mp_Body->GetWorld()->DestroyBody(mp_Body);
}

void StairBrick::OnUpdate(float ts)
{
}

void StairBrick::OnRender()
{
	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *texture);
}

void StairBrick::OnTriggerEnter(IObject* collider)
{
}
