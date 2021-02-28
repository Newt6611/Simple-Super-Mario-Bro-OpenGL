#pragma once

#include "IObject.h"

class Game;

class Ground : public IObject
{
public:
	Ground(Game& game, b2World& physicsWorld);
	~Ground();

	void OnUpdate(float ts) override;
	void OnRender() override;
	void OnTriggerEnter(IObject* collider) override;

private:
	Texture* texture;
	b2Body* mp_Body;

	int width_count = 200;
	float tile_width = 100;
};