#include "game.h"
#include "engine.h"
#include "renderer.h"
#include "ship.h"
#include "fileSystem.h"
#include "enemy.h"

Scene* m_scene = new Scene();

bool Game::Initalize()
{
	bool success = m_engine->Initialize();
	m_scene->Initialize();

	FileSystem::Instance()->SetPathName("..\\content\\galaga\\");
	
	Ship* ship = new Ship(m_scene, "player");
	ship->Create(Vector2D(400, 525));
	m_scene->AddEntity(ship);
	

	for (int i = 0; i < 50; i++)
	{
		Enemy* enemy = new Enemy(m_scene);
		float x = Math::GetRandomRange(0.0f, 800.0f);
		float y = Math::GetRandomRange(-30.0f, -300.0f);
		enemy->Create(Vector2D(x, y));
		m_scene->AddEntity(enemy);
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

	Renderer::Instance()->SetColor(Color::black);
	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}
