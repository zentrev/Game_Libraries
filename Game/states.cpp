#include "states.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "enemy.h"

void TitleState::Enter()
{
	Entity* logo = m_owner->GetScene()->AddEntity<Entity>("logo");
	logo->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = logo->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);

	m_credits = 0;
}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start") == InputManager::eButtonState::PRESSED)
	{
		m_owner->SetState("game");
	}
}

void TitleState::Exit()
{
	Entity* entity = m_owner->GetScene()->GetEntityWithID("logo");
	if (entity)
	{
		entity->SetState(Entity::DESTROY);
	}
}

void GameState::Enter()
{
	for (size_t i = 0; i < 500; i++)
	{
		Enemy* enemy = new Enemy(m_owner->GetScene());
		float x = Math::GetRandomRange(-800.0f, 1600.0f);
		float y = Math::GetRandomRange(-30.0f, -400.0f);
		enemy->Create(Vector2D(x, y));
		m_owner->GetScene()->AddEntity(enemy);
	}
}

void GameState::Update()
{
}

void GameState::Exit()
{
}
