#pragma once

#include "math.h"
#include <assert.h>

class ENGINE_API Color
{
public:
	float r, g, b;

public:
	Color() {}
	Color(float r, float g, float b) : r(r), g(g), b(b) {}
	Color& operator = (const Color & color) { r = color.r; g = color.g; b = color.b; return *this; }

	float& operator [] (size_t index) { assert(index <= 2); return ((&r)[index]); }
	const float& operator [] (size_t index) const { assert(index <= 2); return ((&r)[index]); }

	char ConvertU8(size_t index) const { assert(index <= 2); return static_cast<char>(Math::Clamp01((&r)[index]) * 255.0f); }

	Color& operator += (const Color & color) { r += color.r; g += color.g; b += color.b; return *this; }
	Color& operator -= (const Color & color) { r -= color.r; g -= color.g; b += color.b; return *this; }
	Color& operator *= (const Color & color) { r *= color.r; g *= color.g; b += color.b; return *this; }
	Color& operator /= (const Color & color) { r /= color.r; g /= color.g; b += color.b; return *this; }

	const Color operator + (const Color & color) const { Color c(*this); return c += color; }
	const Color operator - (const Color & color) const { Color c(*this); return c -= color; }
	const Color operator * (const Color & color) const { Color c(*this); return c *= color; }
	const Color operator / (const Color & color) const { Color c(*this); return c /= color; }

	Color& operator += (float s) { r += s; g += s; b += s; return *this; }
	Color& operator -= (float s) { r -= s; g -= s; b -= s; return *this; }
	Color& operator *= (float s) { r *= s; g *= s; b *= s; return *this; }
	Color& operator /= (float s) { r /= s; g /= s; b /= s; return *this; }

	const Color operator + (float s) const { Color color(*this); return color += s; }
	const Color operator - (float s) const { Color color(*this); return color -= s; }
	const Color operator * (float s) const { Color color(*this); return color *= s; }
	const Color operator / (float s) const { Color color(*this); return color /= s; }
		
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color white;
	static const Color orange;
	static const Color yellow;
	static const Color magenta;
	static const Color cyan;
	static const Color black;

	//friend std::ostream & operator << (std::ostream & stream, const Color & color) { stream << "{" << color.r << ", " << color.g << ", " << color.b << "}"; return stream; }
	//friend std::istream & operator >> (std::istream & stream, Color & color);
};

