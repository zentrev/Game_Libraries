#include "ship.h"
#include "kinematicComponent.h"
#include "shipControllerComponent.h"
#include "spriteComponent.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "explosion.h"

void Ship::Create(const Vector2D & position)
{
	SetTag("player");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	ShipControllerComponent* shipController = AddComponent<ShipControllerComponent>();
	shipController->Create(600.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 1.0f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();
}

void Ship::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
}

void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position);
			SetState(Entity::DESTROY);
		}

		if (event.sender->GetTag() == "enemymissile")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position);
			SetState(Entity::DESTROY);
		}
	}
}