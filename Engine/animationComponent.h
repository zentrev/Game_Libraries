#pragma once
#include "component.h"
#include <vector>

class Texture;

class ENGINE_API AnimationComponent : public Component
{
public:
	enum ePlayblack
	{
		LOOP,
		ONE_TIME,
		ONE_TIME_DESTROY,
		BOUNCY_CASTLE
	};
public:
	AnimationComponent(Entity* owner) : Component(owner) {};
	void Create(const std::vector<std::string>& texutreNames, float rate, ePlayblack playback)
	{

	}

protected:
};