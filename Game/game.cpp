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

	//for (int i = 0; i < 10; i++)
	{
		Ship* ship = new Ship(m_scene);

		
		ship->Create(Vector2D(400, 525));
		m_scene->AddEntity(ship);
	}

	Enemy* enemy = new Enemy(m_scene);

	float x = (float)(rand() % 800);
	float y = (float)(rand() % 600);
	enemy->Create(Vector2D(x, y));
	m_scene->AddEntity(enemy);

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
	m_scene->Update();


	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}
