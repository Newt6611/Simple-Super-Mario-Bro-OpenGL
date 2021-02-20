#pragma once

#include "IObject.h"

class Game;

class Coin : public IObject
{
public:
	Coin(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale);
	~Coin();
	void OnUpdate(float ts) override;
	void OnRender() override;
	void OnTriggerEnter(IObject* collider) override;

	void ShootCoin();

private:
	void Animation(float ts);

private:
	bool isAlive = false;
	glm::vec2 shoot_pos;

	bool startCount = false;
	float show_time = 1.5f;
	float show_time_btw = show_time;

	// Animation
	int texutre_index = 0;
	float animation_speed = 0.05f;
	float animation_time_btw = animation_speed;

	Texture* current_texture;
	Texture* textures[6];

	b2Body* mp_Body;

};