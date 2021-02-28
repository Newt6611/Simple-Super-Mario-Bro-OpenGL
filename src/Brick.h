#pragma once

#include "IObject.h"

class Game;

class Brick : public IObject
{
public:
	Brick(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale);
	~Brick();

	void OnUpdate(float ts) override;
	void OnRender() override;

	void OnTriggerEnter(IObject* collider) override;

private:
	const void const Shake(float ts);
private:
	int hp = 3;


	Texture* current_texture;
	Texture* textures[3];

	b2Body* mp_Body;
};