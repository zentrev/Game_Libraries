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
float x;
float y;

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
	text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Inconsolata-Bold.ttf", 24, Color::white);

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


	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_A) == InputManager::eButtonState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_A) == InputManager::eButtonState::HELD)) angle -= 180.0f * Timer::Instance()->DeltaTime();
	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_D) == InputManager::eButtonState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_D) == InputManager::eButtonState::HELD)) angle += 180.0f * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_W) == InputManager::eButtonState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_W) == InputManager::eButtonState::HELD)) force.y = -300.0f * Timer::Instance()->DeltaTime();
	if ((InputManager::Instance()->GetButtonState(SDL_SCANCODE_S) == InputManager::eButtonState::PRESSED) || (InputManager::Instance()->GetButtonState(SDL_SCANCODE_S) == InputManager::eButtonState::HELD)) force.y = 300.0f * Timer::Instance()->DeltaTime();

	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_LEFT) == InputManager::eButtonState::PRESSED) text->SetColor(Color::orange);

	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_RIGHT) == InputManager::eButtonState::HELD) text->SetColor(Color::red);
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_MIDDLE) == InputManager::eButtonState::HELD) text->SetColor(Color::blue);
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_X1) == InputManager::eButtonState::RELEASED) text->SetColor(Color::green);
	if (InputManager::Instance()->GetMouseButtonState(SDL_BUTTON_X2) == InputManager::eButtonState::RELEASED) text->SetColor(Color::yellow);

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;
	
	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);
	
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	//text->SetColor(colors[rand() % colors.size()]);
	x += .013;
	y += .01;
	text->Draw(Vector2D(x, y), 0.0f);

	Renderer::Instance()->DrawTexture(texture, position, angle);

	Renderer::Instance()->EndFrame();
}