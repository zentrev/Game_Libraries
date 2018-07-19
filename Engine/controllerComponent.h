#pragma once

#include "component.h"

class ENGINE_API IControllerComponent : public Component
{
public:
	IControllerComponent(Entity* entity) : Component(entity) {}
};