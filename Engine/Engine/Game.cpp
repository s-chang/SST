#include "Game.h"
#include "EngineHeaders.h"

Game::Game()
{
	//while(!drawQ.empty()) 
	//	drawQ.pop();
	/*while(!textQ.empty())
		textQ.pop();*/
	//RECT r;
	
}

Game::~Game()
{}

void Game::init()
{
	//DELETE  ->
	test1.init();
	test1.setHandle("block");

	test2.init();
	test2.setHandle("FFT");

	//-> HERE

	Engine::Graphics::instance()->init();
	Engine::Sound::instance()->init();
	Engine::Text::instance()->init();
}

void Game::update()
{

	Engine::Sound::instance()->update();


	//Delete from here
	test1.update();
	//test2.update();
	//TO here

}

void Game::render()
{
	if(!Engine::DX::instance()->getDevice())
		return;

	if(SUCCEEDED(Engine::DX::instance()->getDevice()->Clear(0,0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(Engine::DX::instance()->getDevice()->BeginScene()))
		{
			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				//while(!drawQ.empty())
			//	{
			//		Engine::Graphics::instance()->render(drawQ.front());
			//		drawQ.pop();
			//	}
				//DELETE --->
				Engine::Graphics::instance()->render(test1);
				Engine::Graphics::instance()->render(test2);

				//---->Here
				Engine::DX::instance()->getSprite()->End();

				/*while(!textQ.empty())
				{
					Engine::Text::instance()->render(textQ.front().top, textQ.front().left, textQ.front().wordbuffer, textQ.front().color);
					textQ.pop();

				}*/
			}
		}
		Engine::DX::instance()->getDevice()->EndScene();
	}
	Engine::DX::instance()->getDevice()->Present(0,0,0,0);
}

void Game::shutdown()
{
	Engine::Text::instance()->shutdown();
	Engine::Sound::instance()->shutdown();
	Engine::Graphics::instance()->shutdown();
}

void Game::reset()
{}

