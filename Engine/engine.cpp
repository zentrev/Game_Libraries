#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "audioSystem.h"
#include "inputManager.h"
#include "vector2D.h"

#include <cassert>

Vector2D position(0.0f, 0.0f);

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	
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
		case SDLK_DOWN:
			position = position - Vector2D::down;
			break;
		case SDLK_UP:
			position = position - Vector2D::up;
			break;
		case SDLK_RIGHT:
			position = position + Vector2D::right;
			break;
		case SDLK_LEFT:
			position = position + Vector2D::left;
			break;
		}
	}
	
	Renderer::Instance()->BeginFrame();

	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\link.bmp");
	Renderer::Instance()->DrawTexture(texture, position, 0.0f);

	Renderer::Instance()->EndFrame();
	
	//SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	//SDL_RenderClear(m_renderer);

	//// Draw
	//SDL_Rect rect = {x, y, 64, 64 };
	//SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\cat.bmp");

	//SDL_SetRenderDrawColor(m_renderer, 0, 140, 140, 255);
	//SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	//SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect,35.0f, nullptr, SDL_FLIP_HORIZONTAL);

	//SDL_RenderPresent(m_renderer);

}