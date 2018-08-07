#pragma once
#include "entity.h"
#include "vector2D.h"

class Ship : public Entity
{
public:
	Ship(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Ship() {}

	void Create(const Vector2D& position);
	void Update();

	void Ship::OnEvent(const Event& event);

};

