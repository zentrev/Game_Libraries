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


Entity* entity = nullptr;

bool Game::Initalize()
{
	bool success = m_engine->Initialize();


	//Inputs
	InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("up", SDL_SCANCODE_UP, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("down", SDL_SCANCODE_DOWN, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("steer", InputManager::eAxis::X, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("extreamFunk", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

	//Audio
	AudioSystem::Instance()->AddSound("extreamFunk", "..\\content\\Sound Data Hell\\Sonic Rush\\Extreme Funk Synth 2.wav");



	//text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Inconsolata-Bold.ttf", 24, Color::white);


	//test

	entity = new Entity(ID("player"));
	TransformComponent* transformComponent = new TransformComponent(entity);
	transformComponent->Create(Vector2D(30.0f, 30.0f));
	entity->AddComponent(transformComponent);

	SpriteComponent* spriteComponent = new SpriteComponent(entity);
	spriteComponent->Create("..\\content\\car.bmp");
	entity->AddComponent(spriteComponent);

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

	entity->Update();

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::HELD) std::cout << "RawrXD";

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	float steer = InputManager::Instance()->GetActionRelative("steer");
	std::string str = std::to_string(steer);

	//if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)) angle -= 180.0f * Timer::Instance()->DeltaTime();
	//if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD)) angle += 180.0f * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if ((InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD)) force.y = -300.0f * Timer::Instance()->DeltaTime();
	if ((InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD)) force.y = 300.0f * Timer::Instance()->DeltaTime();

	if (InputManager::Instance()->GetActionButton("extreamFunk") == InputManager::eButtonState::HELD)
	{
		AudioSystem::Instance()->PlaySound("extreamFunk");
	}

	Matrix22 mx;
	//angle -= (steer * 200.0f) * Timer::Instance()->DeltaTime();
	//mx.Rotate(angle * Math::DegreesToRadians);
	//force = force * mx;
	//position = position + force;

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	//text->SetColor(colors[rand() % colors.size()]);
	//Renderer::Instance()->DrawTexture(texture, position, angle);

	entity->Draw();

	Renderer::Instance()->EndFrame();
}
