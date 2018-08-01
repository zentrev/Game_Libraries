#pragma once
#include "engine.h"
#include "singleton.h"
#include <fmod.hpp>
#include <string>
#include <map>

class ENGINE_API AudioSystem : public Singleton<AudioSystem>
{
public:
	bool Initialize(Engine* engine);
	void Update();
	void Shutdown();

	void AddSound(const std::string& id, const std::string& audioName);
	void RemoveSound(const std::string& id);
	void PlaySound(const std::string& id);

	friend Singleton<AudioSystem>;

protected:
	AudioSystem() {}
	~AudioSystem() {}

private:
	Engine * m_engine;
	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
};