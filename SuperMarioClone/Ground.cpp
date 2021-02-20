#include "Ground.h"

#include "Game.h"

Ground::Ground(Game& game, b2World& physicsWorld)
{
	game.RegisterGameEvent(*this);
	tag = "ground";

	texture = &Texture::GetTexture("ground");

	b2BodyDef bodyDef;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	bodyDef.position.Set(tile_width * width_count / 2 / Game::PIXEL_TO_M, 100 / Game::PIXEL_TO_M);
	mp_Body = physicsWorld.CreateBody(&bodyDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(tile_width * width_count / 2 / Game::PIXEL_TO_M, 50 / Game::PIXEL_TO_M);
	mp_Body->CreateFixture(&groundShape, 0.0f);
}

Ground::~Ground()
{
	delete texture;
}

void Ground::OnUpdate(float ts)
{

}

void Ground::OnRender()
{
	for (int i = 0; i < width_count; i++)
	{
		Renderer2D::DrawTexture({ i * tile_width, 100 }, 0, {tile_width + 14.5f, tile_width + 20.f }, *texture);
	}
}

void Ground::OnTriggerEnter(IObject* collider)
{
}
