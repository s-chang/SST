#include "Text.h"
#include "DX.h"

Engine::Text::Text()
{
	font = nullptr;
	ZeroMemory(buffer, sizeof(buffer));
	rect.top = rect.bottom = rect.right = rect.left = 0;
	color = D3DCOLOR_ARGB(255,255,255,255);
}

Engine::Text::~Text()
{}

Engine::Text *Engine::Text::instance()
{
	static Text text;
	return &text;
}

void Engine::Text::init()
{
	D3DXCreateFont(Engine::DX::instance()->getDevice(),
		30, 10, FW_NORMAL, 0, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"), &font);
}

void Engine::Text::setText(LPCWSTR text)
{
	swprintf_s(buffer, 256, text);
}

void Engine::Text::render(long top, long left)
{
	rect.top = top;
	rect.left = left;

	font->DrawText(0, buffer, -1, &rect, DT_TOP | DT_LEFT | DT_NOCLIP, color);
}


void Engine::Text::render(long top, long left, wchar_t words[256], dColor color)
{
	rect.top = top;
	rect.left = left;
	font->DrawText(0, words, -1, &rect, DT_TOP|DT_LEFT|DT_NOCLIP, color);
}

void Engine::Text::setColor(dColor color)
{
	this->color = color;
}

void Engine::Text::shutdown()
{
	SAFE_RELEASE(font);
}