#include "Pipe.h"
#include "Game.h"	

Pipe::Pipe(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale)
{
	game.RegisterGameEvent(*this);

	m_Position = position;
	m_Scale = scale;
	m_Rotation = 0;
	tag = "pipe";

	texture = &Texture::GetTexture("pipe");

	b2BodyDef b_def;
	b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b_def.type = b2_staticBody;
	b_def.position.Set(m_Position.x / Game::PIXEL_TO_M, m_Position.y / Game::PIXEL_TO_M);
	mp_Body = physicsWorld.CreateBody(&b_def);

	b2PolygonShape b_shape;
	b_shape.SetAsBox(scale.x / 2 / Game::PIXEL_TO_M, scale.y / 2 / Game::PIXEL_TO_M);
	mp_Body->CreateFixture(&b_shape, 0.0);
}

Pipe::~Pipe() 
{
	mp_Body->GetWorld()->DestroyBody(mp_Body);
}

void Pipe::OnUpdate(float ts) { }

void Pipe::OnRender() 
{
	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *texture);
}

void Pipe::OnTriggerEnter(IObject* collider) { }
