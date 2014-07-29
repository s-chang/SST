#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef D3DXCOLOR dXColor;

class Light
{
private:
	D3DLIGHT9 light;
	bool b_light;

public:
	Light();
	~Light();

	void defaultInit();

	void setPosition(float x, float y, float z);
	void setAmbient(dXColor color);
	void setDiffuse(dXColor color);
	void setSpecular(dXColor color);
	void setType(D3DLIGHTTYPE value);
	void setRange(float num);
	void setAttenuation(float zero, float one, float two);

	D3DXVECTOR3 getPosition();
	dXColor getAmbient();
	dXColor getDiffuse();
	dXColor getSpecular();
	D3DLIGHTTYPE getType();
	float getRange();
	float getAttenuation0();
	float getAttenuation1();
	float getAttenuation2();

	void setLight();
	void toggleLight(bool on_off);
};