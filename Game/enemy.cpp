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
#include "enemyTargetControllerComponent.h"
#include "transformControllerComponent.h"
#include "timer.h"

std::vector<Vector2D> Enemy::m_enterPath = {
	Vector2D(200.0f, 400.0f),
	Vector2D(300.0f, 300.0f),
	Vector2D(200.0f, 200.0f),
	Vector2D(100.0f, 300.0f),
	Vector2D(200.0f, 400.0f)
};

void Enemy::Create(const Vector2D & position, const Vector2D & targetPosition)
{
	SetTag("enemy");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	m_targetPosition = targetPosition;

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(50000.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();

	AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");

	m_stateMachine = new StateMachine(GetScene(), this);
	m_stateMachine->AddState("enter_path", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("enter_formation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("atack", new AttackState(m_stateMachine));
	m_stateMachine->SetState("enter_path");
}

void Enemy::Update()
{
	Entity::Update();

	m_stateMachine->Update();

	Vector2D size = Renderer::Instance()->GetSize();
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

void EnterPathState::Enter()
{
	EnemyWaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<EnemyWaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_speed, Enemy::m_enterPath);
}
void EnterPathState::Update()
{
	EnemyWaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<EnemyWaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_formation");
	}
}
void EnterPathState::Exit()
{

}

void EnterFormationState::Enter()
{
	EnemyWaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<EnemyWaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_speed, std::vector<Vector2D> { m_owner->GetEntity<Enemy>()->m_targetPosition });
}

void EnterFormationState::Update()
{
	EnemyWaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<EnemyWaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("idle");
	}
}

void EnterFormationState::Exit()
{

}

void IdleState::Enter()
{
	TransformControllerComponent* controller = m_owner->GetEntity()->AddComponent<TransformControllerComponent>();
	controller->Create(m_owner->GetEntity<Enemy>()->m_targetPosition, 180.0f, m_owner->GetEntity<Enemy>()->m_speed, 5.0f);

	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
}

void IdleState::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		TransformControllerComponent* controller = m_owner->GetEntity()->GetComponent<TransformControllerComponent>();
		m_owner->GetEntity()->RemoveComponent(controller);
		m_owner->SetState("atack");
	}
}

void IdleState::Exit()
{
}

void AttackState::Enter()
{
	EnemyWaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<EnemyWaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_speed, Enemy::m_enterPath);
}
void AttackState::Update()
{
	EnemyWaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<EnemyWaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_formation");
	}
}
void AttackState::Exit()
{
	m_owner->GetEntity()->GetTransform().position.y = -64.0f;
}