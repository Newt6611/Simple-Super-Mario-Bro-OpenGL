#pragma once

#include "GL/glew.h"
#include "box2d/box2d.h"
#include "IObject.h"
#include "Camera.h"
#include "Renderer2D.h"
#include "Mario.h"
#include "Ground.h"
#include "Mushroom.h"
#include "ContactListener.h"
#include "CoinBrick.h"
#include "Coin.h"
#include "Brick.h"
#include "Level.h"

#include <vector>


class Game 
{
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void OnInit();
	void OnUpdate(float ts);
	void OnRender();

public:
	void RegisterGameEvent(IObject& object);
	void UnRegisterGameEvent(IObject& object);

	void LoadAllShader();
	void LoadAllTexture();

public:
	static float PIXEL_TO_M;

private:
	Camera camera;
	
	unsigned int width, height;
	std::vector<IObject*> scene_objects;
	
	Mario* mario;
	Ground* ground;
	Level* level;

	

	// physics
	b2World* physicsWorld;
	ContactListener* contactListener;

};