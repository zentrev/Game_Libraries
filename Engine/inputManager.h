#pragma once
#include "engine.h"
#include "singleton.h"
#include "vector2D.h"
#include <vector>
#include <map>

class InputManager : public Singleton<InputManager>
{
public:
	enum eButtonState
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

	enum eDivice
	{
		KEYBOARD,
		MOUSE,
		CONTROLLER
	};

	enum eAxis
	{
		X,
		Y
	};

	struct InputInfo
	{
		eDivice device;
		int id;
		int index;
	};

	struct ControllerInfo
	{
		SDL_GameController* controller;
		Uint8 buttonstate[SDL_CONTROLLER_BUTTON_MAX];
		Uint8 prevButtonstate[SDL_CONTROLLER_BUTTON_MAX];
		float axis[SDL_CONTROLLER_AXIS_MAX];
		float prevAxis[SDL_CONTROLLER_AXIS_MAX];
	};

public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	eButtonState GetButtonState(SDL_Scancode scancode);
	eButtonState GetMouseButtonState(int button);

	friend Singleton<InputManager>;

protected:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;

	int m_numKeys;
	Uint8 * m_keystate;
	Uint8 * m_prevKeystate;

	Uint32 m_buttonstate;
	Uint32 m_prevButtonstate;
	Vector2D m_mousePosition;
	Vector2D m_prevMousePosition;

	std::vector<ControllerInfo> m_controllers;

	std::map<std::string, InputInfo> m_actions;

};

