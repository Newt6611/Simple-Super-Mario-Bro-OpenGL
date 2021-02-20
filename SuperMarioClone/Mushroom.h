#pragma once

#include "IObject.h"

class Game;

class Mushroom : public IObject
{
public:
	Mushroom(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale);
	~Mushroom();

	void OnUpdate(float ts) override;
	void OnRender() override;
	void OnTriggerEnter(IObject* object) override;

private:
	void RunAnimation(float ts);
	void CountToDie(float ts);

private:
	bool isAlive = true;
	bool isDie = false; // For delay dead texture
	float time_to_dispear = 1.f;

	float speed = 2.f;
	bool faceRight = false;

	Texture* current_texture;
	Texture* run_texture[2];
	Texture* dead_texture;

	// Animation
	int texture_index = 0;
	float animation_speed = 0.1f;
	float animation_time_btw = animation_speed;


	b2Body* mp_Body;
};