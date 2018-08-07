#include "ship.h"
#include "shipControllerComponent.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "renderer.h"
#include "aabbComponent.h"

void Ship::Create(const Vector2D& position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SetTag("player");

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(1600.0f, 0.1f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.5f));

	ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	shipControllerComponent->Create(650);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();
}

void Ship::Update()
{
	Entity::Update();
	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
	
	
	//m_transform.scale = size;
}

void Ship::OnEvent(const Event& event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy")
		{
			SetState(Entity::DESTORY);
		}
	}
}
