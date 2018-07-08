#pragma once
#include "engine.h"
#include "color.h"
#include <iostream>

class text
{
public:
	text(const std::string& text, const std::string& font, int size, Color& color);
	~text();
};

