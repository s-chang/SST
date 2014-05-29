#include "RawInput.h"
#include <windowsx.h>

Engine::RawInput::RawInput()
{
	xPos = yPos = 0;	
}

Engine::RawInput::~RawInput()
{}

Engine::RawInput *Engine::RawInput::instance()
{
	static RawInput rawinput;
	return &rawinput;
}

void Engine::RawInput::setX(LPARAM lparam)
{
	xPos = GET_X_LPARAM(lparam);
}

void Engine::RawInput::setY(LPARAM lparam)
{
	yPos = GET_Y_LPARAM(lparam);
}

int Engine::RawInput::getX()
{
	return xPos;
}

int Engine::RawInput::getY()
{
	return yPos;
}

int Engine::RawInput::getButton(WPARAM wparam)
{
	switch(wparam)
	{
	case MK_LBUTTON:
		return LEFT_BUTTON;
		break;
	case MK_MBUTTON:
		return MIDDLE_BUTTON;
		break;
	case MK_RBUTTON:
		return RIGHT_BUTTON;
		break;
	}
}




