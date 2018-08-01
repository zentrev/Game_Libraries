#include "enemy.h"
#include "shipControllerComponent.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"

void Enemy::Create(const Vector2D& position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(1600.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01a.png", Vector2D(0.5f, 0.5f));

	//ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	//shipControllerComponent->Create(250);
}

void Enemy::
Update()
{
	Entity::Update();
}

