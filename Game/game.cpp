#include "game.h"
#include "engine.h"
#include "audioSystem.h"
#include "text.h"
#include "textManager.h"
#include "inputManager.h"
#include "color.h"
#include "renderer.h"
#include "textureManager.h"
#include "singleton.h"
#include "timer.h"
#include "_math.h"
#include "matrix22.h"
#include "matrix33.h"
#include "vector2D.h"
#include "vector3D.h"
#include "entity.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"
#include "scene.h"

Entity* entity = nullptr;
Scene* scene = new Scene();

bool Game::Initalize()
{
	bool success = m_engine->Initialize();
	scene->Initialize();

	for (int i = 0; i < 10; i++)
	{

		float x = 300;
		float y = i * 50;

		entity = new Entity(ID("player"));
		TransformComponent* transformComponent = new TransformComponent(entity);
		transformComponent->Create(Vector2D(x, y));
		entity->AddComponent(transformComponent);

		SpriteComponent* spriteComponent = new SpriteComponent(entity);
		spriteComponent->Create("..\\content\\Sprites\\ship.png");
		entity->AddComponent(spriteComponent);

		ShipControllerComponent* shipControllerComponent = new ShipControllerComponent(entity);
		shipControllerComponent->Create((i+1) * 250);
		entity->AddComponent(shipControllerComponent);

		scene->AddEntity(entity);
	}

	m_running = success;
	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->IsQuit();
	m_engine->Update();
	scene->Update();


	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	scene->Draw();

	Renderer::Instance()->EndFrame();
}
