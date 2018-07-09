#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "audioSystem.h"
#include "inputManager.h"
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"
#include "textManager.h"
#include <cassert>
#include <iostream>

Vector2D position(10.0f, 10.0f);
float angle = 0.0f;
Text* text;

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);	
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	
	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);
	text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Inconsolata-Bold.ttf", 24, Color::red);

	return true;
}

void Engine::Shutdown()
{
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextManager::Instance()->Shutdown();
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTimeScale(1.0f);
	InputManager::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			m_isQuit = true;
			break;
		}
	}

	SDL_PumpEvents();
	InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_LEFT);


	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_A) == InputManager::eState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_A) == InputManager::eState::HELD)) angle -= 90.0f * Timer::Instance()->DeltaTime();
	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_D) == InputManager::eState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_D) == InputManager::eState::HELD)) angle += 90.0f * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_W) == InputManager::eState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_W) == InputManager::eState::HELD)) force.y = -200.0f * Timer::Instance()->DeltaTime();
	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_S) == InputManager::eState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_S) == InputManager::eState::HELD)) force.y = 200.0f * Timer::Instance()->DeltaTime();

	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_LEFT) == InputManager::eState::PRESSED) std::cout << "Left Pressed\n";
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_LEFT) == InputManager::eState::HELD) std::cout << "Left Held\n";
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_LEFT) == InputManager::eState::RELEASED) std::cout << "Left Reseased\n";

	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_RIGHT) == InputManager::eState::HELD) std::cout << "Right Held\n";
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_MIDDLE) == InputManager::eState::HELD) std::cout << "Middle Held\n";
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_X1) == InputManager::eState::HELD) std::cout << "X1 Held\n";
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_X2) == InputManager::eState::HELD) std::cout << "X2 Held\n";

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;
	
	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);
	
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetColor(colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	Renderer::Instance()->DrawTexture(texture, position, angle);

	Renderer::Instance()->EndFrame();

}