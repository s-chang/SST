#include "CWindow.h"
#include "RawInput.h"


CWindow::CWindow()
{
	ZeroMemory(&wndClass, sizeof(wndClass));
}

CWindow::~CWindow()
{}

void CWindow::init(HWND &hWnd, HINSTANCE &hInstance, bool windowed)
{
	wndClass.cbSize			= sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;
	wndClass.lpszClassName	= WINDOW_TITLE;
	wndClass.hInstance		= hInstance;
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH)(COLOR_WINDOWFRAME);

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(
		WINDOW_TITLE, WINDOW_TITLE,
		windowed ? WS_OVERLAPPEDWINDOW | WS_VISIBLE : (WS_POPUP|WS_VISIBLE),
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	//handle messages
	switch(message)
	{
	case WM_PAINT:
		{
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_KEYDOWN:
		{
			Engine::RawInput::instance()->getButton(wparam);
			switch(wparam)
			{
			case VK_ESCAPE:
				{
					PostQuitMessage(0);
					break;
				}
			}
		}

	case WM_MOUSEMOVE:
		{
			Engine::RawInput::instance()->setX(lparam);
			Engine::RawInput::instance()->setY(lparam);
			Engine::RawInput::instance()->getButton(wparam);
		}
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}