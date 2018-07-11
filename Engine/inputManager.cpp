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

	m_buttonstate = SDL_GetMouseState(nullptr , nullptr);
	m_prevButtonstate = m_buttonstate;

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			ControllerInfo controllerInfo;
			controllerInfo.controller = SDL_GameControllerOpen(i);
			memset(controllerInfo.buttonstate, 0, SDL_CONTROLLER_BUTTON_MAX);
			memset(controllerInfo.prevButtonstate, 0, SDL_CONTROLLER_BUTTON_MAX);
			memset(controllerInfo.axis, 0, SDL_CONTROLLER_AXIS_MAX);
			memset(controllerInfo.prevAxis, 0, SDL_CONTROLLER_AXIS_MAX);
			m_controllers.push_back(controllerInfo);
		}
	}

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

	SDL_Point axis;
	m_prevButtonstate = m_buttonstate;
	m_buttonstate = SDL_GetMouseState(&axis.x, &axis.y);
	m_prevMousePosition = m_mousePosition;
	m_mousePosition = axis;
}

InputManager::eButtonState InputManager::GetButtonState(SDL_Scancode scancode)
{
	eButtonState state = eButtonState::IDLE;

	if (m_keystate[scancode])
	{
		state = (m_prevKeystate[scancode]) ? eButtonState::HELD : eButtonState::PRESSED;
	}
	else
	{
		state = (m_prevKeystate[scancode]) ? eButtonState::RELEASED : eButtonState::IDLE;
	}

	return state;
}

InputManager::eButtonState InputManager::GetMouseButtonState(int button)
{
	eButtonState state = eButtonState::IDLE;

	if (m_buttonstate & SDL_BUTTON(button))
	{
		state = (m_prevButtonstate & SDL_BUTTON(button)) ? eButtonState::HELD : eButtonState::PRESSED;
	}
	else
	{
		state = (m_prevButtonstate & SDL_BUTTON(button)) ? eButtonState::RELEASED : eButtonState::IDLE;
	}

	return state;
}
