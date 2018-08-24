#pragma once
#include "controllerComponent.h"
#include "vector2D.h"

class TransformControllerComponent : public IControllerComponent
{
public:
	TransformControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& position, float rotation, float speed, float rotateRate);
	void Destroy();
	void Update();

protected:
	Vector2D m_position;
	float m_rotation;
	float m_speed;
	float m_rotateRate;
};