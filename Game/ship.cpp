#include "ship.h"
#include "shipControllerComponent.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"

void Ship::Create(const Vector2D& position)
{
	m_transform.position = position;

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(1600.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("..\\content\\Sprites\\ship.png");

	ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	shipControllerComponent->Create(250);
}
