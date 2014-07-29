#pragma once


#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef D3DXVECTOR3 dxVec3;
typedef D3DXMATRIX  dxMatrix;


class Camera
{
private:
	dxVec3 m_eyePos;
	dxVec3 m_lookAt;
	dxVec3 m_upVec;

	dxMatrix m_viewMat;
	dxMatrix m_projMat;

	float m_degrees;
	float m_near;
	float m_far;

public:

	Camera();
	~Camera();

	void init();

	void setProj(int width, int height);

	void setLookAt(float x, float y, float z);
	void setEyePos(float x, float y, float z);

	dxVec3 getEyePos();
	dxMatrix getView();
	dxMatrix getProjection();

};
