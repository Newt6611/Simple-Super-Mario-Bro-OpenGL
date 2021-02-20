#pragma once

#include <iostream>

#include "Game.h"
#include "Renderer2D.h"
#include "Shader.h"
#include "Texture.h";

float Game::PIXEL_TO_M = 150.f;

Game::Game(unsigned int width, unsigned int height) :
	width(width), height(height), camera(0, width, 0, height)
{

}

Game::~Game()
{
	Renderer2D::OnShutDown();
	delete contactListener;
	delete level;

	delete physicsWorld;
}

void Game::OnInit()
{	
	LoadAllShader();
	LoadAllTexture();


	Renderer2D::OnInit();

	// Physics Init
	b2Vec2 gravity(0, -20);
	this->physicsWorld = new b2World(gravity); // gravity -10
	contactListener = new ContactListener(*physicsWorld);

	mario = new Mario(*this, *physicsWorld);
	ground = new Ground(*this, *physicsWorld);
	level = new Level(*this, *physicsWorld);
}

void Game::OnUpdate(float ts)
{
	for (int i = 0; i < scene_objects.size(); i++)
		scene_objects[i]->OnUpdate(ts);

	camera.SetPosition({ mario->GetPosition().x - (width / 2), camera.GetPosition().y });


	// physics update
	physicsWorld->Step(ts, 8, 3);
}

void Game::OnRender()
{
	Renderer2D::BeginScene(camera);

	
	for (int i = 0; i < scene_objects.size(); i++)
		scene_objects[i]->OnRender();

	Renderer2D::EndScene();
}


void Game::RegisterGameEvent(IObject& object)
{
	scene_objects.push_back(&object);
}

void Game::UnRegisterGameEvent(IObject& object)
{
	for (int i = 0; i < scene_objects.size(); i++)
	{
		if (scene_objects[i] == &object)
			scene_objects.erase(scene_objects.begin() + i);
	}
}


void Game::LoadAllShader()
{
	Shader::LoadShader("sprite", "Shader/Sprite.vert.glsl", "Shader/Sprite.frag.glsl");
	Shader::LoadShader("flat", "Shader/FlatColor.vert.glsl", "Shader/FlatColor.frag.glsl");
}

void Game::LoadAllTexture()
{
	// Mario
	Texture::LoadTexture("mario-idle", "Texture/Mario/mario-idle.png", true);
	Texture::LoadTexture("mario-run-0", "Texture/Mario/mario-run0.png", true);
	Texture::LoadTexture("mario-run-1", "Texture/Mario/mario-run1.png", true);
	Texture::LoadTexture("mario-run-2", "Texture/Mario/mario-run2.png", true);
	Texture::LoadTexture("mario-jump", "Texture/Mario/mario-jump.png", true);

	// Ground
	Texture::LoadTexture("ground", "Texture/ground.png", true);

	// Bad Mushroom
	Texture::LoadTexture("mushroom-run-0", "Texture/Mushroom/mushroom-run0.png", true);
	Texture::LoadTexture("mushroom-run-1", "Texture/Mushroom/mushroom-run1.png", true);
	Texture::LoadTexture("mushroom-dead", "Texture/Mushroom/mushroom-dead.png", true);

	// Brick
	Texture::LoadTexture("brick-0", "Texture/Brick/brick-0.png", true);
	Texture::LoadTexture("brick-1", "Texture/Brick/brick-1.png", true);
	Texture::LoadTexture("brick-2", "Texture/Brick/brick-2.png", true);

	// Coin Brick
	Texture::LoadTexture("coin-brick-idle", "Texture/CoinBrick/coin-brick.png", true);
	Texture::LoadTexture("coin-brick-break", "Texture/CoinBrick/coin-break-brick.png", true);

	// Coin 
	Texture::LoadTexture("coin-0", "Texture/Coin/coin-0.png", true);
	Texture::LoadTexture("coin-1", "Texture/Coin/coin-1.png", true);
	Texture::LoadTexture("coin-2", "Texture/Coin/coin-2.png", true);
	Texture::LoadTexture("coin-3", "Texture/Coin/coin-3.png", true);
	Texture::LoadTexture("coin-4", "Texture/Coin/coin-4.png", true);
	Texture::LoadTexture("coin-5", "Texture/Coin/coin-5.png", true);

	// Pipe
	Texture::LoadTexture("pipe", "Texture/pipe.png", true);

	// Stair Brick
	Texture::LoadTexture("stair_brick", "Texture/StairBrick.png", true);
}