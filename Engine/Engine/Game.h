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
	
	void reset();
	
public:
	Game();
	~Game();

	void init();

	void update();
	void render();

	void shutdown();
};