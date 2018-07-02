#pragma once
#include <iostream>
#include "SDL.h"

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

class TextureManager;

class ENGINE_API Engine
{
public:
	Engine() { }
	~Engine() {}

	bool Initialize();
	void Update();
	void Shutdown();

	SDL_Window* GetWindow() { return m_window; }

	bool IsQuit() { return m_isQuit; }

	void Display() { std::cout << "Hello World!"; }

protected:
	bool m_isQuit = false;
	SDL_Window * m_window = nullptr;
	
};
