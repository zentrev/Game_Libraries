#pragma once
#include "engine.h"
#include "singleton.h"

class AudioSystem : public Singleton<AudioSystem>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	friend Singleton<AudioSystem>;

protected:
	AudioSystem() {}
	~AudioSystem() {}

private:
	Engine * m_engine;
};