#include "audioSystem.h"
#include "fileSystem.h"
#include <cassert>

bool AudioSystem::Initialize(Engine * engine)
{
	m_engine = engine;
	FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
	void* extradriverdata = nullptr;
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	assert(result == FMOD_OK);
	return true;
}

void AudioSystem::Update()
{
}

void AudioSystem::Shutdown()
{
	for(auto& sound : m_sounds)
	{
		sound.second->release();
	}
	m_fmodSystem->close();
	m_fmodSystem->release();
}

void AudioSystem::AddSound(const std::string & id, const std::string & audioName)
{
	auto iter = m_sounds.find(id);
	if (iter == m_sounds.end())
	{
		std::string filename = FileSystem::Instance()->GetPathName() + audioName;
		FMOD::Sound* _sound = nullptr;
		m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, &_sound);
		m_sounds[id] = _sound;
	}
}

void AudioSystem::RemoveSound(const std::string & id)
{
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		iter->second->release();
		m_sounds.erase(iter);
	}
}

void AudioSystem::PlaySound(const std::string & id)
{
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		m_fmodSystem->playSound(m_sounds[id], nullptr, 0, nullptr);
	}
}


