#define VC_EXTRALEAN
#include "CWindow.h"
#include "DX.h"
#include "Timer.h"
#include "Game.h"

#include <fstream>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HWND myhWnd = NULL;
	HINSTANCE myInstance = hInstance;
	bool window = true;

	//create window for use
	CWindow myWindow;
	myWindow.init(myhWnd, myInstance, window);

	//Initialize Timer
	Engine::Timer::instance()->init();

	//Init DirectX
	Engine::DX::instance()->init(myhWnd, window);
	

	//create game here
	Game game;
	game.init();

	//Use msg structure to catch window messages
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while(msg.message != WM_QUIT)
	{
		
		//hide cursor
		ShowCursor(false);

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}else
		{

			Engine::Timer::instance()->update();
			//add update/render code here
			game.update(msg);
			game.render();
			Sleep(1);
		}
	}

	//shutdown game
	game.shutdown();


	//Release DirectX
	Engine::DX::instance()->shutdown();
	
	UnregisterClass(WINDOW_TITLE, myInstance);
	return 0;
}