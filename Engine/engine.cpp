#include "engine.h"
#include "textureManager.h"

#include <cassert>

//To-Do
//InputManager
//Renderer
//AudioSystem


bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	TextureManager::Instance()->Initialize(this);

	return true;
}

void Engine::Shutdown()
{
	TextureManager::Instance()->Shutdown();
	SDL_DestroyRenderer(m_renderer);
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
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
	}
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// Draw
	SDL_Rect rect = {x, y, 64, 64 };
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\cat.bmp");

	SDL_SetRenderDrawColor(m_renderer, 0, 140, 140, 255);
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect,35.0f, nullptr, SDL_FLIP_HORIZONTAL);

	SDL_RenderPresent(m_renderer);

}