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

	mesh1.init();
//	mesh1.setScale(5.0f, 5.0f, 5.0f);
	mesh1.setHandle("grem");
	mesh1.set3D(true);



	//-> HERE

	Engine::Graphics::instance()->init();
	Engine::Sound::instance()->init();
	Engine::Text::instance()->init();
}

void Game::update(MSG &msg)
{

	Engine::Sound::instance()->update();

	this->msg = msg;
	//Delete from here
	test1.update();

	float y = mesh1.getRotate().y + Engine::Timer::instance()->getDT() * 5.0f;
	if( y > 360)
		y = 0;
	mesh1.setRotate(mesh1.getRotate().x, y, mesh1.getRotate().z);
	//mesh1.update();
	//test2.update();
	/*static float x = 0.0f;

	x += Engine::Timer::instance()->getDT();

	if(x >= 3.0f)
	{
		x = 0.0f;

		if(Engine::DX::instance()->isWindowed())
			Engine::DX::instance()->fullscreen();
		else
			Engine::DX::instance()->windowed();
		

	}*/
	
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
				//Engine::Graphics::instance()->render(test1);
				//Engine::Graphics::instance()->render(test2);

				Engine::Graphics::instance()->render(mesh1);

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

