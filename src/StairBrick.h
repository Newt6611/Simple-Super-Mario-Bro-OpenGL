#pragma once

#include "IObject.h"

class Game;


class StairBrick : public IObject
{
public:
	StairBrick(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale);
	~StairBrick();

	void OnUpdate(float ts) override;
	void OnRender() override;
	void OnTriggerEnter(IObject* collider) override;

private:
	Texture* texture;
	b2Body* mp_Body;
};