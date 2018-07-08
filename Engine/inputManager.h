#pragma once
#include "engine.h"
#include "singleton.h"

class InputManager : public Singleton<InputManager>
{
public:
	enum eState
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	eState GetButtonState(SDL_Scancode scancode);
	eState GetMouseButtonState(int button);

	friend Singleton<InputManager>;

protected:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
	Uint8 * m_keystate;
	Uint8 * m_prevKeystate;
	Uint32 m_buttonstate;
	Uint32 m_prevButtonstate;
	int m_numKeys;

};

