/**
Written by: Smyth Chang
Description: The CWindow class creates a window for use.
*/

#pragma once
#include <Windows.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE L"Engine test"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

class CWindow
{
private:
	WNDCLASSEX wndClass;

public:
	CWindow();
	~CWindow();

	void init(HWND &hWnd, HINSTANCE &hInstance, bool windowed);
};