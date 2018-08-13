#include "game.h"
#include "engine.h"
#include "renderer.h"
#include "scene.h"
#include "ship.h"
#include "enemy.h"
#include "fileSystem.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "textComponent.h"
#include "eventManager.h"

bool Game::Initalize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathname("..\\content\\galaga\\");

	EventManager::Instance()->SetGameEventReceiver(this);
	
	m_scene = new Scene();

	//Entity* entity = new Entity(m_scene);
	//entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	//SpriteComponent* spriteComponent = entity->AddComponent<SpriteComponent>();
	//spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	//spriteComponent->SetDepth(100);
	//m_scene->AddEntity(entity);

	/*Entity* explosion = new Entity(m_scene);
	explosion->GetTransform().position = Vector2D(400.0f, 300.0f);
	explosion->GetTransform().scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = explosion->AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animationComponent = explosion->AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames = {"ship-explosion01.png", "ship-explosion02.png", "ship-explosion03.png", "ship-explosion04.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f);
	m_scene->AddEntity(explosion);*/

	Entity* entity = new Entity(m_scene, "score");
	entity->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* textComponent = entity->AddComponent<TextComponent>();
	textComponent->Create("00000", "emulogic.ttf", 18, Color::white);
	textComponent->SetDepth(100);
	m_scene->AddEntity(entity);


	Ship* ship = new Ship(m_scene, "player");
	ship->Create(Vector2D(400, 510));
	m_scene->AddEntity(ship);

	for (size_t i = 0; i < 5; i++)
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

	Entity* scoreEntity = m_scene->GetEntityWithID("score");
	if (scoreEntity)
	{
		TextComponent* textComponent = scoreEntity->GetComponent<TextComponent>();
		std::string score = std::to_string(m_score);
		while (score.length() < 5) score = "0" + score;
		textComponent->SetText(score);
	}
	
	Renderer::Instance()->SetColor(Color::black);
	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.eventID == "add_score")
	{
		m_score = m_score + 100;
	}
}

