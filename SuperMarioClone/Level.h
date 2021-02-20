#pragma once

#include "IObject.h"
#include "Brick.h"
#include "CoinBrick.h"
#include "Pipe.h"
#include "Mushroom.h"
#include "StairBrick.h"

class Game;

class Level : public IObject
{
public:
	Level(Game& game, b2World& physicsWorld);
	~Level();

	void OnUpdate(float ts) override;
	void OnRender() override;
	void OnTriggerEnter(IObject* collider) override;

private:
	const char* map;
	std::vector<IObject*> objects;

};