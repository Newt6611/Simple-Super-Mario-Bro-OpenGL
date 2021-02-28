#include "Mushroom.h"

#include "Game.h"

Mushroom::Mushroom(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale)
{
	m_Position = position;
	m_Rotation = 0;
	m_Scale = scale;

	game.RegisterGameEvent(*this);

	run_texture[0] = &Texture::GetTexture("mushroom-run-0");
	run_texture[1] = &Texture::GetTexture("mushroom-run-1");
	dead_texture = &Texture::GetTexture("mushroom-dead");
	current_texture = run_texture[0];
	tag = "mushroom";

	b2BodyDef b_def;
	b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b_def.type = b2_dynamicBody;
	b_def.fixedRotation = true;
	b_def.position.Set(m_Position.x / Game::PIXEL_TO_M, m_Position.y / Game::PIXEL_TO_M);
	b_def.angle = glm::radians(m_Rotation);

	this->mp_Body = physicsWorld.CreateBody(&b_def);

	b2PolygonShape box_shape;
	box_shape.SetAsBox(m_Scale.x / 2.f / Game::PIXEL_TO_M, m_Scale.y / 2.f / Game::PIXEL_TO_M);

	b2FixtureDef fixDef;
	fixDef.shape = &box_shape;
	fixDef.density = 1;
	fixDef.friction = 0.3f;
	this->mp_Body->CreateFixture(&fixDef);
}

Mushroom::~Mushroom()
{
	delete run_texture[0];
	delete run_texture[1];
	delete current_texture;
	delete dead_texture;
}

void Mushroom::OnUpdate(float ts)
{
	if (!isAlive)
		return;

	m_Position = { mp_Body->GetPosition().x * 150, mp_Body->GetPosition().y * 150 };
	m_Rotation = glm::degrees(mp_Body->GetAngle());

	b2Vec2 vel = mp_Body->GetLinearVelocity();
	if (faceRight)
		vel.x = speed;
	else
		vel.x = -speed;
	mp_Body->SetLinearVelocity(vel);
		
	if (isDie)
		CountToDie(ts);

	if(current_texture != dead_texture)
		RunAnimation(ts);
}

void Mushroom::OnRender()
{
	if (!isAlive)
		return;
	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *current_texture);
}



void Mushroom::OnTriggerEnter(IObject* collider)
{
	if (isDie || !isAlive)
		return;
	faceRight = !faceRight;

	if (collider->tag == "mario")
	{
		if (collider->GetPosition().y > m_Position.y)
		{
			isDie = true;
			current_texture = dead_texture;
		}
	}
}

void Mushroom::CountToDie(float ts)
{
	speed = 0;
	if (time_to_dispear < 0)
	{
		mp_Body->GetFixtureList()->SetSensor(true);
		isAlive = false;
	}
	else
	{
		time_to_dispear -= ts;
	}
}


void Mushroom::RunAnimation(float ts)
{
	current_texture = run_texture[texture_index];

	if (animation_time_btw > 0)
	{
		animation_time_btw -= ts;
	}
	else
	{
		animation_time_btw = animation_speed;
		texture_index++;
		if (texture_index >= 2)
			texture_index = 0;
	}
}