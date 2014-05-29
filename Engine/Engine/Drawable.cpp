#include "Drawable.h"

Drawable::Drawable()
{
	translate = rotate = dVec3(0,0,0);
	scale = dVec3(1.0f, 1.0f, 1.0f);
	color = D3DCOLOR_ARGB(255,255,255,255);
	height = width = 0;
	isOn = false;
	isSpritesheet = false;
	is3D = false;
	rect.bottom = rect.left = rect.right = rect.top = 0;
	draw = true;
	
}

Drawable::~Drawable()
{}

void Drawable::setIsOn(bool a_isOn)
{
	isOn = a_isOn;
}

bool Drawable::getIsOn()
{
	return isOn;
}

dVec3 Drawable::getTranslate()
{
	return translate;
}

dVec3 Drawable::getScale()
{
	return scale;
}

dVec3 Drawable::getRotate()
{
	return rotate;
}

void Drawable::setTranslate(float x, float y, float z)
{
	translate.x = x;
	translate.y = y;
	translate.z = z;
}

void Drawable::setScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Drawable::setRotate(float x, float y, float z)
{
	rotate.x = x;
	rotate.y = y;
	rotate.z = z;
}

void Drawable::setRect(RECT r)
{
	//rect = r;
	rect.bottom = r.bottom;
	rect.top = r.top;
	rect.right = r.right;
	rect.left = r.left;
}

RECT Drawable::getRect()
{
	return rect;
}

bool Drawable::checkOn(float x, float y, int scale)
{
	return (x < (translate.x + (width / scale)) && x > (translate.x -  (width / scale)) &&
		y < (translate.y + (height / scale)) && y > (translate.y -  (height / scale)));
}

void Drawable::setColor(dColor a_color)
{
	color = a_color;
}

dColor Drawable::getColor()
{
	return color;
}



void Drawable::init()
{
	
}

void Drawable::init(dVec3 translate, dVec3 scale, dVec3 rotate, dColor color, RECT rect, bool isSpriteSheet, bool is3D, bool draw)
{
	this->translate = translate;
	this->scale = scale;
	this->rotate = rotate;
	this->color = color;
	this->rect = rect;
	this->isSpritesheet = isSpriteSheet;
	this->is3D = is3D;
	this->draw = draw;
}

void Drawable::update()
{}

void Drawable::reset()
{}

int Drawable::getWidth()
{
	return width;
}

int Drawable::getHeight()
{
	return height;
}

bool Drawable::getIsSpriteSheet()
{
	return isSpritesheet;
}

bool Drawable::get3D()
{
	return is3D;
}

bool Drawable::getDraw()
{
	return draw;
}

void Drawable::setDraw(bool arg)
{
	draw = arg;
}

void Drawable::setHandle(std::string name)
{
	handle = name;
}

std::string Drawable::getHandle()
{
	return handle;
}

