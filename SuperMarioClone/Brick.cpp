#include "Brick.h"
#include "Game.h"

Brick::Brick(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale)
{
	game.RegisterGameEvent(*this);

	m_Position = position;
	m_Scale = scale;
	m_Rotation = 0;
	tag = "brick";

	textures[0] = &Texture::GetTexture("brick-2");
	textures[1] = &Texture::GetTexture("brick-1");
	textures[2] = &Texture::GetTexture("brick-0");
	current_texture = textures[2];


	b2BodyDef b_def;
	b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b_def.position.Set(m_Position.x / Game::PIXEL_TO_M, m_Position.y / Game::PIXEL_TO_M);
	b_def.type = b2_dynamicBody;
	b_def.fixedRotation = true;
	b_def.gravityScale = 0;
	mp_Body = physicsWorld.CreateBody(&b_def);

	b2PolygonShape b_shape;
	b_shape.SetAsBox(m_Scale.x / 2.f / Game::PIXEL_TO_M, m_Scale.y / 2.f / Game::PIXEL_TO_M);
	mp_Body->CreateFixture(&b_shape, 0.0f);
}

Brick::~Brick()
{
	/*
	if(mp_Body)
		mp_Body->GetWorld()->DestroyBody(mp_Body);
	*/
}

void Brick::OnUpdate(float ts)
{
	m_Position = { mp_Body->GetPosition().x * Game::PIXEL_TO_M, mp_Body->GetPosition().y * Game::PIXEL_TO_M };
	m_Rotation = mp_Body->GetAngle();
}

void Brick::OnRender()
{
	if(hp > 0)
		Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *current_texture);
}

void Brick::OnTriggerEnter(IObject* collider)
{
	if (collider->tag == "mario")
	{
		if (collider->GetPosition().y < m_Position.y)
		{
			hp--;
			if (hp <= 0)
				mp_Body->GetFixtureList()->SetSensor(true);
			current_texture = textures[hp - 1];
		}
	}
}

