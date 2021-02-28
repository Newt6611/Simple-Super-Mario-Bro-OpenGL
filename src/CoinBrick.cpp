#include "CoinBrick.h"
#include "Game.h"

CoinBrick::CoinBrick(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale)
{
	game.RegisterGameEvent(*this);

	m_Position = position;
	m_Rotation = 0;
	m_Scale = scale;
	tag = "coin-brick";


	idle_texture = &Texture::GetTexture("coin-brick-idle");
	break_texture = &Texture::GetTexture("coin-brick-break");
	current_texture = idle_texture;

	b2BodyDef b_def;
	b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b_def.position.Set(m_Position.x / Game::PIXEL_TO_M, m_Position.y / Game::PIXEL_TO_M);
	b_def.fixedRotation = true;
	mp_Body = physicsWorld.CreateBody(&b_def);

	b2PolygonShape b_shape;
	b_shape.SetAsBox(m_Scale.x / 2 / Game::PIXEL_TO_M, m_Scale.y / 2 / Game::PIXEL_TO_M);
	mp_Body->CreateFixture(&b_shape, 0.0f);


	coin = new Coin(game, physicsWorld, m_Position, m_Scale);
}

CoinBrick::~CoinBrick()
{
	mp_Body->GetWorld()->DestroyBody(mp_Body);
	delete coin;
}

void CoinBrick::OnUpdate(float ts)
{

}

void CoinBrick::OnRender()
{
	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *current_texture);
}

void CoinBrick::OnTriggerEnter(IObject* collider)
{
	if (collider->tag == "mario" && collider->GetPosition().y < m_Position.y)
	{
		if (current_texture == idle_texture)
		{
			coin->ShootCoin();
			current_texture = break_texture;
		}
		else if (current_texture == break_texture)
			return;
	}
}
