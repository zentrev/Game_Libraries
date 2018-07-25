#include "kinematicComponent.h"
#include "timer.h"
#include "physics.h"
#include "engine.h"
#include "transformComponent.h"
#include "entity.h"

void KinematicComponent::Create(float velocityMax, float dampening, bool enableGravity)
{
	m_velocityMax = velocityMax;
	m_dampening = dampening;
	m_enableGravity = enableGravity;

	m_forceType = eForceType::FORCE;
	m_force = Vector2D::zero;
	m_velocity = Vector2D::zero;
}

void KinematicComponent::Destroy()
{
	//
}

void KinematicComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	Vector2D force = (m_enableGravity) ? m_force + Physics::Instance()->GetGravity() : m_force;

	m_velocity = m_velocity + force * dt;
	float length = m_velocity.Length();
	if (length > m_velocityMax)
	{
		m_velocity = m_velocity.Normalized() * m_velocityMax;
	}

	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	if (transform)
	{
		transform->position = transform->position + (m_velocity *dt);
	}
}

void KinematicComponent::ApplyForce(const Vector2D & force, eForceType forceType)
{
	m_force = force;
}

