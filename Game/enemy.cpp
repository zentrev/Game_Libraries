#include "enemy.h"
#include "enemyControllerComponent.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "renderer.h"

void Enemy::Create(const Vector2D& position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(1600.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01a.png", Vector2D(0.5f, 0.5f));

	EnemyControllerComponent* enemyControllerComponent = AddComponent<EnemyControllerComponent>();
	enemyControllerComponent->Create(250);
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

