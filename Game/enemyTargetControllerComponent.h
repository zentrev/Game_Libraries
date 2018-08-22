#pragma once
#include "controllerComponent.h"
#include "vector2D.h"

class EnemyTargetControllerComponent : public IControllerComponent
{
public:
	EnemyTargetControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& target, float speed);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
	Vector2D m_target;
};