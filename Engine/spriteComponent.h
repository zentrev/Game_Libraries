#pragma once

#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "renderComponent.h"

class Texture;

class ENGINE_API SpriteComponent : public IRenderComponent
{
public:
	SpriteComponent(Entity* owner) : IRenderComponent(owner) {}

	void Create(const std::string& textureName, const Vector2D& origin = Vector2D::zero);
	void Destroy();
	void Update();

	void Draw();

	Texture* GetTexture() { return m_texture; }
	const Vector2D& GetOrgin() { return m_orgin; }

protected:
	Texture* m_texture;
	Vector2D m_orgin;
	Vector2D m_uv1;
	Vector2D m_uv2;
};
