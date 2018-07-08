#pragma once
#include "engine.h"
#include "singleton.h"
class Timer : public Singleton<Timer>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	float DeltaTime() const { return m_dt * m_timeSacle; }
	float UnscaledDeltaTime() const { return m_dt; }

	void SetTimeScale(float timeScale) { m_timeSacle = timeScale; }
	float getTimeSacle() { return m_timeSacle; }

	void Pause() { m_paused = true; }
	void Unpause() { m_paused = false; }
	bool IsPaused() const { return m_paused; }

	friend Singleton<Timer>;

protected:
	Timer() {}

private:
	Engine * m_engine;
	float m_dt;
	float m_timeSacle;
	bool m_paused;
	Uint32 m_prevTicks;
};

