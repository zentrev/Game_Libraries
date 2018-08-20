#include "enemyWaypointControllerComponent.h"
#include "timer.h"
#include "entity.h"
#include "waypoint.h"
#include "missile.h"
#include "kinematicComponent.h"
#include <iostream>

void EnemyWaypointControllerComponent::Create(float speed, std::vector<Vector2D> points)
{
	m_speed = speed;
	m_fireRateMin = 1.0f;
	m_fireRateMax = 3.0f;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_owner->GetScene()->AddEntity<Waypoint>();
		waypoint->Create(point, Vector2D(40.0f, 40.0f), m_owner);
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
	
	float angle = Vector2D::GetAngle(force) * Math::RadiansToDegrees + 90;
	float rotation = m_owner->GetTransform().rotation;

	//if (angle < -89)
	//{
	//	rotation = Math::Lerp(m_owner->GetTransform().rotation, angle, (5 * dt));
	//	//std::cout << "- rot: " << rotation << "\n";
	//}
	//else if (angle > 269)
	//{
	//	rotation = Math::Lerp(m_owner->GetTransform().rotation, angle, (5 * dt + .7));
	//	std::cout << "+ rot: " << rotation << "\n";
	//}
	//else

	if (angle > 0 && m_owner->GetTransform().rotation < 0)
	{
		rotation = angle;

		std::cout << angle << " : " << m_owner->GetTransform().rotation << " : " << rotation << "\n";
	}
	else if (angle < 0 && m_owner->GetTransform().rotation > 0)
	{
		rotation = angle;
		std::cout << angle << " : " << m_owner->GetTransform().rotation << " : " << rotation << "\n";
	}
	else
	{
		rotation = Math::Lerp(m_owner->GetTransform().rotation, angle, (5 * dt));
	}
	m_owner->GetTransform().rotation = rotation;

	Vector2D newForce = Vector2D::down;
	newForce = Vector2D::Rotate(newForce, rotation * Math::DegreesToRadians);
	newForce.Normalize();

	

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(newForce * m_speed, KinematicComponent::VELOCITY);
	}

	/*Vector2D force = m_waypoint->GetTransform().position - m_owner->GetTransform().position;
	force.Normalize();

	float rotation = Vector2D::GetAngle(force) * Math::RadiansToDegrees + 90;
	m_owner->GetTransform().rotation = Math::Lerp(m_owner->GetTransform().rotation, rotation, (2 * dt));

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::FORCE);
	}*/
/*
	Vector2D force = m_waypoint->GetTransform().position - m_owner->GetTransform().position;
	force.Normalize();

	float rotation = Vector2D::GetAngle(force) * Math::RadiansToDegrees +90;
	m_owner->GetTransform().rotation = Math::Lerp(m_owner->GetTransform().rotation, rotation, (2 * dt));

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}*/

	

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
