#pragma once

#include "IObject.h"
#include "Coin.h"

class Game;

class CoinBrick : public IObject
{
public:
	CoinBrick(Game& game, b2World& physicsWorld, glm::vec2 position, glm::vec2 scale);
	~CoinBrick();

	void OnUpdate(float ts) override;
	void OnRender();

	void OnTriggerEnter(IObject* collider) override;


private:
	Coin* coin;

	Texture* current_texture;
	Texture* idle_texture;
	Texture* break_texture;

	b2Body* mp_Body;
};