
#include "Mario.h"

#include "Game.h"


Mario::Mario(Game& game, b2World& physicsWorld)
{
	m_Position = glm::vec2(800, 2000);
	m_Rotation = 0;
	m_Scale = glm::vec2(100, 100);
	tag = "mario";
	game.RegisterGameEvent(*this);

	// textures init
	idle_texture = &Texture::GetTexture("mario-idle");
	jump_texture = &Texture::GetTexture("mario-jump");
	run_texture[0] = &Texture::GetTexture("mario-run-0");
	run_texture[1] = &Texture::GetTexture("mario-run-1");
	run_texture[2] = &Texture::GetTexture("mario-run-2");

	current_texture = idle_texture;

	// physics init
	b2BodyDef b_def;
	b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b_def.type = b2_dynamicBody;
	b_def.fixedRotation = true;
	b_def.gravityScale = 2.f;
	b_def.position.Set(m_Position.x / Game::PIXEL_TO_M, m_Position.y / Game::PIXEL_TO_M);
	b_def.angle = glm::radians(m_Rotation);

	this->mp_Body = physicsWorld.CreateBody(&b_def);
	b2PolygonShape box_shape;
	box_shape.SetAsBox(m_Scale.x / 2.f / Game::PIXEL_TO_M, m_Scale.y / 2.f / Game::PIXEL_TO_M);
	
	b2FixtureDef fixDef;
	fixDef.shape = &box_shape;
	fixDef.density = 1;
	fixDef.friction = 1.f;
	this->mp_Body->CreateFixture(&fixDef);
}

Mario::~Mario()
{
	delete idle_texture;
	delete current_texture;
	delete jump_texture;
	for (int i = 0; i < 3; i++)
		delete run_texture[i];
}

void Mario::OnUpdate(float ts)
{
	// Getting imformation from box2D's world and translate to world space.
	m_Position = { mp_Body->GetPosition().x * 150, mp_Body->GetPosition().y * 150 };
	m_Rotation = glm::degrees(mp_Body->GetAngle());
	////////////////////////////////////////////////////////////////////////

	Movement(ts);



	// Animation
	if ((Input::GetKey(GLFW_KEY_LEFT) || Input::GetKey(GLFW_KEY_RIGHT)) != 0 && !jumping)
	{
		RunAnimation(ts);
	}
	else if (jumping)
	{
		current_texture = jump_texture;
	}
	else if(current_texture != idle_texture && !jumping)
	{
		current_texture = idle_texture;
	}

	// For Flip Character
	if (Input::GetKey(GLFW_KEY_LEFT) && faceRight)
		Flip();
	else if (Input::GetKey(GLFW_KEY_RIGHT) && !faceRight)
		Flip();
}

void Mario::OnRender()
{
	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *current_texture);
}


void Mario::Movement(float ts)
{
	b2Vec2 vel = mp_Body->GetLinearVelocity();
	if (Input::GetKey(GLFW_KEY_LEFT))
		vel.x = -speed;
	else if (Input::GetKey(GLFW_KEY_RIGHT))
		vel.x = speed;

	// Jump
	if (Input::GetKeyDown(GLFW_KEY_SPACE))
		Jump(vel);

	mp_Body->SetLinearVelocity(vel);
}

void Mario::Jump(b2Vec2& vel)
{
	if (!jumping)
	{
		jumping = true;
		vel.y = jumpForce;
		current_texture = jump_texture;
	}
}

void Mario::LittleJump()
{
	b2Vec2 vel = mp_Body->GetLinearVelocity();
	vel.y = 10;
	current_texture = jump_texture;
	mp_Body->SetLinearVelocity(vel);
}


void Mario::OnTriggerEnter(IObject* collider)
{
	jumping = false;
	if (collider->tag == "mushroom")
		LittleJump();
}







void Mario::Flip()
{
	faceRight = !faceRight;
	m_Scale.x *= -1;
}

void Mario::RunAnimation(float ts)
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
		if (texture_index >= 3)
			texture_index = 0;
	}
}
