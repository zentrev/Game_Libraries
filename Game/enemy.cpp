#include "enemy.h"
#include "enemyControllerComponent.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "explosion.h"

void Enemy::Create(const Vector2D& position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SetTag("enemy");

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(1600.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01a.png", Vector2D(0.5f, 0.5f));

	EnemyControllerComponent* enemyControllerComponent = AddComponent<EnemyControllerComponent>();
	enemyControllerComponent->Create(250);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f, 0.7f));
}

void Enemy::
Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	if (m_transform.position.y > size.y + 64.0f)
	{
		float x = Math::GetRandomRange(0.0f, size.x);
		float y = -100.0f;
		m_transform.position = Vector2D(x, y);
	}
	//m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
	//m_transform.position.y = Math::Clamp(m_transform.position.y, 0.0f, size.y);

}

void Enemy::OnEvent(const Event& event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playermissile")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTORY);
		}
		if (event.sender->GetTag() == "player")
		{
			SetState(Entity::DESTORY);
		}
	}
}

