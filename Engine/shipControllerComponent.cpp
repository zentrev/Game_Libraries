#include "shipControllerComponent.h"
#include "inputManager.h"
#include "transformComponent.h"
#include "entity.h"
#include "timer.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
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
		force.x += -1.0;
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force.x += 1.0;
	}

	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	transform->position = transform->position + (force * m_speed * Timer::Instance()->DeltaTime());
}