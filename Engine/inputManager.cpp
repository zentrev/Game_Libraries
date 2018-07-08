#include "inputManager.h"
#include <string.h>
#include <iostream>

bool InputManager::Initialize(Engine * engine)
{
	m_engine = engine;

	SDL_GetKeyboardState(&m_numKeys);
	m_keystate = new Uint8[m_numKeys];
	m_prevKeystate = new Uint8[m_numKeys];

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);
	memcpy(m_prevKeystate, m_keystate, m_numKeys);

	m_buttonstate = 0;
	m_prevButtonstate = m_buttonstate;

	return true;
}

void InputManager::Shutdown()
{
	delete m_keystate;
	delete m_prevKeystate;
}

void InputManager::Update()
{
	memcpy(m_prevKeystate, m_keystate, m_numKeys);
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);

	m_prevButtonstate = m_buttonstate;
	m_buttonstate = SDL_GetMouseState(NULL,NULL);
}

InputManager::eState InputManager::GetButtonState(SDL_Scancode scancode)
{
	eState state = eState::IDLE;

	if (m_keystate[scancode])
	{
		state = (m_prevKeystate[scancode]) ? eState::HELD : eState::PRESSED;
	}
	else
	{
		state = (m_prevKeystate[scancode]) ? eState::RELEASED : eState::IDLE;
	}

	return state;
}

InputManager::eState InputManager::GetMouseButtonState(int button)
{
	eState state = eState::IDLE;

	if (m_buttonstate & SDL_BUTTON(button))
	{
		state = (m_prevButtonstate & SDL_BUTTON(button)) ? eState::HELD : eState::PRESSED;
	}
	else
	{
		state = (m_prevButtonstate & SDL_BUTTON(button)) ? eState::RELEASED : eState::IDLE;
	}

	return state;
}
