#include "TestObj.h"

#include "RawInput.h"

TestObj::TestObj() : Drawable()
{
	
}

TestObj::~TestObj()
{}

void TestObj::init()
{
	Drawable::init();
	x = y = z = 0.0f;
}

void TestObj::update()
{
	//x += (float)Engine::Input::instance()->get_MouseX();
	//y += (float)Engine::Input::instance()->get_MouseY();

	x = (float)Engine::RawInput::instance()->getX();
	y = (float)Engine::RawInput::instance()->getY();
	
	setTranslate(x, y, 0);
	
}

void TestObj::reset()
{}