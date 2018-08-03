#pragma once
#include "component.h"
#include "engine.h"

class ENGINE_API ICollisionComponent : public Component
{
public:
	ICollisionComponent(Entity* owner) : Component(owner) {}
	~ICollisionComponent() {}

	virtual bool Intersects(ICollisionComponent* other) = 0;

};
