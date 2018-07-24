#include "text.h"

Text::Text(const std::string & text, const std::string & fontName, int size, const Color & color)
{
	m_text = text.c_str();
	m_font = TTF_OpenFont(fontName.c_str(), size);
	m_color = color;
	Create();
}

Text::~Text()
{
	SDL_DestroyTexture(m_texture);
	TTF_CloseFont(m_font);
}

void Text::Draw(const Vector2D & position, float angle)
{
	if (m_texture)
	{
		Renderer::Instance()->DrawTexture(m_texture, position, angle);
	}
}

void Text::SetText(const std::string & text)
{
	if (m_text != text)
	{
		m_text = text;
		Create();
	}

}

void Text::SetText(const std::string & text, const Color & color)
{
	if (m_text != text || m_color != color)
	{
		m_text = text;
		m_color = color;
		Create();
	}
}

void Text::SetColor(const Color & color)
{
	if (m_color != color)
	{
		m_color = color;
		Create();
	}
}

void Text::Create()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}

	SDL_Surface * surface = TTF_RenderText_Solid(m_font, m_text.c_str(), SDL_Color(m_color));
	m_texture = SDL_CreateTextureFromSurface(Renderer::Instance()->GetRenderer(), surface);
	SDL_FreeSurface(surface);
}
