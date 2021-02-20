#include "Coin.h"

#include "Game.h"

Coin::Coin(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale)
{
	game.RegisterGameEvent(*this);

	m_Position = position;
	m_Rotation = 0;
	m_Scale = scale;
	shoot_pos = m_Position;

	textures[0] = &Texture::GetTexture("coin-0");
	textures[1] = &Texture::GetTexture("coin-1");
	textures[2] = &Texture::GetTexture("coin-2");
	textures[3] = &Texture::GetTexture("coin-3");
	textures[4] = &Texture::GetTexture("coin-4");
	textures[5] = &Texture::GetTexture("coin-5");

	current_texture = textures[0];

	b2BodyDef b_def;
	b_def.type = b2_dynamicBody;
	b_def.gravityScale = 0;
	b_def.fixedRotation = true;
	b_def.position.Set(m_Position.x / Game::PIXEL_TO_M, m_Position.y / Game::PIXEL_TO_M);
	mp_Body = physicsWorld.CreateBody(&b_def);

	b2PolygonShape box_shape;
	box_shape.SetAsBox(m_Scale.x / 2.f / Game::PIXEL_TO_M, m_Scale.y / 2.f / Game::PIXEL_TO_M);
	
	b2FixtureDef fixDef;
	fixDef.shape = &box_shape;
	fixDef.density = 1;
	fixDef.friction = 1.f;
	this->mp_Body->CreateFixture(&fixDef);
	mp_Body->GetFixtureList()->SetSensor(true);
}

Coin::~Coin()
{
	mp_Body->GetWorld()->DestroyBody(mp_Body);
}

void Coin::OnUpdate(float ts)
{
	if (isAlive)
	{
		m_Position = { mp_Body->GetPosition().x * Game::PIXEL_TO_M, mp_Body->GetPosition().y * Game::PIXEL_TO_M };
		Animation(ts);
	}

	if (startCount)
	{
		if (show_time_btw <= 0)
		{
			startCount = false;
			isAlive = false;
			show_time_btw = show_time;
			mp_Body->SetGravityScale(0);
		}
		else
		{
			show_time_btw -= ts;
		}
	}
}

void Coin::OnRender()
{
	if (isAlive)
	{
		Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *current_texture);
	}
}

void Coin::ShootCoin()
{
	isAlive = true;
	startCount = true;
	mp_Body->SetGravityScale(3);
	b2Vec2 vel = mp_Body->GetLinearVelocity();
	vel.y = 15;
	mp_Body->SetLinearVelocity(vel);
}

void Coin::Animation(float ts)
{
	if (animation_time_btw <= 0 )
	{
		texutre_index++;
		if (texutre_index >= 6)
			texutre_index = 0;

		current_texture = textures[texutre_index];
		animation_time_btw = animation_speed;
	}
	else 
	{
		animation_time_btw -= ts;
	}
}

void Coin::OnTriggerEnter(IObject* collider)
{

}