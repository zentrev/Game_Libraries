#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "enemyControllerComponent.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "explosion.h"
#include "enemyWaypointControllerComponent.h"

void Enemy::Create(const Vector2D & position)
{
	SetTag("enemy");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	/*EnemyControllerComponent* controller = AddComponent<EnemyControllerComponent>();
	controller->Create(200.0f);*/
	EnemyWaypointControllerComponent* controller = AddComponent<EnemyWaypointControllerComponent>();
	std::vector<Vector2D> points = { Vector2D(300.0f,300.0f), Vector2D(500.0f,400.0f), Vector2D(96.0f,-480.0f) };
	controller->Create(200.0f, points);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();

	AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
}

void Enemy::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	if (m_transform.position.y > size.y + 64.0f)
	{
		float x = Math::GetRandomRange(0.0f, size.x);
		float y = -100.0f;
		m_transform.position = Vector2D(x, y);
	}
}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playermissile")
		{
 			Event _event;
			_event.eventID = "add_score";
			_event.variants[0].asInteger = 111;
			_event.variants[0].type = Variant::INTERGER;
			EventManager::Instance()->SendGameMessage(_event);

			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position);
			SetState(Entity::DESTROY);
		}
		if (event.sender->GetTag() == "player")
		{
			SetState(Entity::DESTROY);
		}
	}
}
