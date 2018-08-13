#include "explosion.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "audioSystem.h"
#include "animationComponent.h"

void Explosion::Create(const Vector2D& position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SetTag("exploion");

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.5f));

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames{ "ship-explosion01.png", "ship-explosion02.png" , "ship-explosion03.png" , "ship-explosion04.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);

	AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
	AudioSystem::Instance()->PlaySound("explosion");
}

void Explosion::Update()
{
	Entity::Update();
}
