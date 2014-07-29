#include "Light.h"
#include "DX.h"

Light::Light()
{
}

Light::~Light()
{}

void Light::defaultInit()
{
	ZeroMemory(&light, sizeof(light));

	light.Ambient = dXColor(1.0f, 1.0f, 1.0f, 1.0f);
	light.Diffuse = dXColor(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = dXColor(1.0f, 1.0f, 1.0f, 1.0f);
	light.Type = D3DLIGHT_POINT;
	light.Position = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	light.Range = 500.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	b_light = true;
}

void Light::setLight()
{
	Engine::DX::instance()->getDevice()->SetLight(0, &light);
	Engine::DX::instance()->getDevice()->LightEnable(0, b_light);
}

void Light::toggleLight(bool on_off)
{
	b_light = on_off;
}

void Light::setPosition(float x, float y, float z)
{
	light.Position = D3DXVECTOR3(x, y, z);
}

void Light::setAmbient(dXColor color)
{
	light.Ambient = color;
}

void Light::setDiffuse(dXColor color)
{
	light.Diffuse = color;
}

void Light::setSpecular(dXColor color)
{
	light.Specular = color;

}

void Light::setType(D3DLIGHTTYPE value)
{
	light.Type = value;
}

void Light::setRange(float num)
{
	light.Range = num;
}

void Light::setAttenuation(float zero, float one, float two)
{
	light.Attenuation0 = zero;
	light.Attenuation1 = one;
	light.Attenuation2 = two;
}

D3DXVECTOR3 Light::getPosition()
{
	return light.Position;
}

dXColor Light::getAmbient()
{
	return light.Ambient;
}

dXColor Light::getDiffuse()
{
	return light.Diffuse;
}

dXColor Light::getSpecular()
{
	return light.Specular;
}

D3DLIGHTTYPE Light::getType()
{
	return light.Type;
}

float Light::getRange()
{
	return light.Range;
}

float Light::getAttenuation0()
{
	return light.Attenuation0;
}

float Light::getAttenuation1()
{
	return light.Attenuation1;
}

float Light::getAttenuation2()
{
	return light.Attenuation2;
}

