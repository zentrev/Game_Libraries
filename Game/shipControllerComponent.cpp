#include "shipControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "timer.h"
#include "entity.h"
#include "kinematicComponent.h"
#include "missile.h"
#include "audioSystem.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

	AudioSystem::Instance()->AddSound("fire", "laser.wav");
}

void ShipControllerComponent::Destroy()
{

}

void ShipControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;
	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
		force = force + Vector2D::left;
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force = force + Vector2D::right;
	}

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::vector<Entity*> missiles = m_owner->GetScene()->GetEnitiesWithTag("playermissile");
		if (missiles.size() < 4)
		{
			Missile* missile = new Missile(m_owner->GetScene());
			missile->Create(m_owner->GetTransform().position, Vector2D::down, 2500.0f);
			m_owner->GetScene()->AddEntity(missile);
			AudioSystem::Instance()->PlaySound("fire");
		}
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::FORCE);
	}	
}