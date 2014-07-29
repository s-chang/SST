#pragma once

#include "Drawable.h"

class TestObj : public Drawable
{
private:
	float x, y, z;
public:
	TestObj();
	~TestObj();

	virtual void init();
	virtual void update();
	virtual void reset();
};