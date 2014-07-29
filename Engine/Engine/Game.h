#pragma once

#include "TestObj.h"
#include <queue>

class Game
{
private:
	//std::queue<Drawable> drawQ;

	//TODO: create a better storage for text
	/*struct TextData
	{
		wchar_t *wordbuffer;
		int top;
		int left;
		D3DCOLOR color;
	};

	std::queue<TextData> textQ;*/
	
	TestObj test1;
	TestObj test2;

	TestObj mesh1;
	
	void reset();

	MSG msg;
	
public:
	Game();
	~Game();

	void init();

	void update(MSG &msg);
	void render();

	void shutdown();
};