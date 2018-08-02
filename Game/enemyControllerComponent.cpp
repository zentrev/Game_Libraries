#include "enemyControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "timer.h"
#include "entity.h"
#include "kinematicComponent.h"
#include "missile.h"
#include "audioSystem.h"

void EnemyControllerComponent::Create(float speed)
{
	m_speed = speed;	
}

void EnemyControllerComponent::Destroy()
{

}

void EnemyControllerComponent::Update()
{
	Vector2D force = Vector2D::up;

	Entity* player = m_owner->GetScene()->GetEntityWithID("player");
	if (player)
	{
		float dx = player->GetTransform().position.x - m_owner->GetTransform().position.x;
		if (dx < -32.0f) force.x = -1.0f;
		if (dx > 32.0f) force.x = 1.0f;
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::FORCE);
	}
}