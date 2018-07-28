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
#include "scene.h"
#include "ship.h"

Scene* m_scene = new Scene();

bool Game::Initalize()
{
	bool success = m_engine->Initialize();
	m_scene->Initialize();

	//for (int i = 0; i < 10; i++)
	{
		Ship* ship = new Ship(m_scene);

		float x = (float)(rand() % 800);
		float y = (float)(rand() % 600);
		ship->Create(Vector2D(x, y));
		m_scene->AddEntity(ship);
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
	m_scene->Update();


	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}
