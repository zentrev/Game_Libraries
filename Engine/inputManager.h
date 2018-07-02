#pragma once
#include "engine.h"
#include "singleton.h"

class InputManager : public Singleton<InputManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	friend Singleton<InputManager>;

protected:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
};

