#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "audioSystem.h"
#include "inputManager.h"
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"

#include <cassert>

Vector2D position(10.0f, 10.0f);
float angle = 0.0f;

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	
	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);

	return true;
}

void Engine::Shutdown()
{
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTimeScale(1.0f);

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

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_LEFT]) angle -= 90.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_RIGHT]) angle += 90.0f * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if (keystate[SDL_SCANCODE_UP]) force.y = -200.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_DOWN]) force.y = 200.0f * Timer::Instance()->DeltaTime();


	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;
	
	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);

	Renderer::Instance()->EndFrame();

}