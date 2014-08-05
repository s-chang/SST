#include "Camera.h"
#include "DX.h"

Camera::Camera()
{}

Camera::~Camera()
{}

void Camera::init()
{
	m_eyePos = dxVec3(5.0f, 5.0f, -10.0f);
	m_lookAt = dxVec3(0.0f, 0.0f, 0.0f);
	m_upVec = dxVec3(0.0f, 1.0f, 0.0f);

	m_degrees = 45.0f;
	m_near = 1.0f;
	m_far = 100.0f;
}

void Camera::setProj(int width, int height)
{
	//Calculate the view matrix 
	D3DXMatrixLookAtLH( &m_viewMat,
		&m_eyePos,
		&m_lookAt,
		&m_upVec);

	//Transform the matrix
	Engine::DX::instance()->getDevice()->SetTransform(D3DTS_VIEW, &m_viewMat);

	//calculate the projection matrix
	//D3DXMatrixOrthoLH( &m_projMat, width, height, m_near, m_far);
	D3DXMatrixPerspectiveFovLH(&m_projMat,
								D3DXToRadian(m_degrees),
								(float)width / (float) height,
								m_near,
								m_far);
								
							

	//Transform
	Engine::DX::instance()->getDevice()->SetTransform(D3DTS_PROJECTION, &m_projMat);

}

void Camera::setLookAt(float x, float y, float z)
{
	m_lookAt.x = x;
	m_lookAt.y = y;
	m_lookAt.z = z;
}

void Camera::setEyePos(float x, float y, float z)
{
	m_eyePos.x = x;
	m_eyePos.y = y;
	m_eyePos.z = z;
}

dxVec3 Camera::getEyePos()
{
	return m_eyePos;
}

dxMatrix Camera::getView()
{
	return m_viewMat;
}

dxMatrix Camera::getProjection()
{
	return m_projMat;
}