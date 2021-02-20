#pragma once

#include "IObject.h"

class Game;

class Mario : public IObject
{
public:
	Mario(Game& game, b2World& physicsWorld);
	~Mario();
	void OnUpdate(float ts) override;
	void OnRender() override;

	// physics
	void OnTriggerEnter(IObject* collider) override;

private:
	void Movement(float ts);
	void Flip();
	void RunAnimation(float ts);
	void Jump(b2Vec2& vel);
	void LittleJump();
	
private:
	float speed = 5.f;
	bool jumping = false;
	float jumpForce = 17;
	bool faceRight = true;


	// Animation
	int texture_index = 0;
	float animation_speed = 0.1f;
	float animation_time_btw = animation_speed;

	Texture* current_texture;
	Texture* idle_texture;
	Texture* jump_texture;
	Texture* run_texture[3];

	// Physics
	b2Body* mp_Body;
};