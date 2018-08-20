#pragma once
#include "aabb.h"

namespace Debug
{
	void DrawAABB(const AABB& aabb, const Color& color = Color::red);
	void DrawLine(const Vector2D& v1, const Vector2D& v2, const Color& color = Color::red);
	void DrawCross(const Vector2D& v1, const Vector2D& size, const Color& color = Color::red);
}

#ifdef _DEBUG
	#define DEBUG_DRAW_AABB(aabb, color)	  Debug::DrawAABB(aabb, color);
	#define DEBUG_DRAW_LINE(v1, v2, color)	  Debug::DrawAABB(v1, v2, color);
	#define DEBUG_DRAW_CROSS(v1, size, color) Debug::DrawAABB(v1, size, color);
#else
	#define DEBUG_DRAW_AABB(aabb, color); 
	#define DEBUG_DRAW_LINE(v1, v2, color);
	#define DEBUG_DRAW_CROSS(v1, size, color);
#endif

