#pragma once

#include "component.h"

class ENGINE_API IRenderComponent : public Component
{
public:
	IRenderComponent(Entity* owner) : Component(owner) {}

	virtual void Draw() = 0;

	void SetVisible(bool visible = true) { m_visible = visible; }
	bool IsVisible() const { return m_visible; }

	void SetDepth(int depth) { m_depth = depth; }
	int GetDepth() { return m_depth; }
	
	static bool CompareDepth(IRenderComponent* renderComponent1, IRenderComponent* renderComponent2)
	{
		return (renderComponent1->m_depth < renderComponent2->m_depth);
	}

protected:
	bool m_visible = true;
	int m_depth = 0;
};