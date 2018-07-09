#pragma once
#include "engine.h"
#include "singleton.h"
#include "text.h"
#include<vector>

class TextManager : public Singleton<TextManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

	friend Singleton<TextManager>;

protected:
	TextManager();
	~TextManager();
private:
	Engine * m_engine;
	std::vector<Text*> m_texts;
};

