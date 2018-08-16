#include "enemyWaypointControllerComponent.h"
#include "timer.h"
#include "entity.h"
#include "waypoint.h"
#include "missile.h"
#include "kinematicComponent.h"

void EnemyWaypointControllerComponent::Create(float speed, std::vector<Vector2D> points)
{
	m_speed = speed;
	m_fireRateMin = 1.0f;
	m_fireRateMax = 3.0f;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_owner->GetScene()->AddEntity<Waypoint>();
		waypoint->Create(point, Vector2D(10.0f, 10.0f), m_owner);
		m_waypoints.push_back(waypoint);
	}
	m_waypointIndex = 0;
	m_waypoint = m_waypoints[m_waypointIndex];
}

void EnemyWaypointControllerComponent::Destroy()
{
	for (Waypoint* waypoints : m_waypoints)
	{
		waypoints->SetState(Entity::DESTROY);
	}
}

void EnemyWaypointControllerComponent::Update()
{
	if (m_owner->Intersects(m_waypoint))
	{
		SetNewxtWaypoint();
	}

	float dt = Timer::Instance()->DeltaTime();

	Vector2D force = m_waypoint->GetTransform().position - m_owner->GetTransform().position;
	force.Normalize();

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	float rotation = Vector2D::GetAngle(force) * Math::RadiansToDegrees + 90;
	m_owner->GetTransform().rotation = Math::Lerp(m_owner->GetTransform().rotation, rotation, (5 * dt));

	m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create("enemymissile", m_owner->GetTransform().position, Vector2D::up, 800.0f);
		m_owner->GetScene()->AddEntity(missile);
	}
}

void EnemyWaypointControllerComponent::SetNewxtWaypoint()
{
	m_waypointIndex++;
	if (m_waypointIndex < m_waypoints.size())
	{
		m_waypoint = m_waypoints[m_waypointIndex];
	} 
	else
	{
		m_owner->SetState(Entity::DESTROY);
	}
}
