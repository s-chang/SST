#include "DX.h"


Engine::DX::DX()
{
	bVsync = false;
	pD3DObject = nullptr;
	pD3DDevice = nullptr;
	pD3DSprite = nullptr;
}

Engine::DX::~DX()
{
	
}

Engine::DX* Engine::DX::instance()
{
	static DX dx;
	return &dx;
}

void Engine::DX::init(HWND &hWnd, bool a_window)
{
	m_hWnd = hWnd;
	window = a_window;

	pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);


	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));

	D3Dpp.hDeviceWindow							= m_hWnd;
	D3Dpp.Windowed								= window;
	D3Dpp.AutoDepthStencilFormat				= D3DFMT_D24S8;
	D3Dpp.EnableAutoDepthStencil				= TRUE;
	D3Dpp.BackBufferCount						= 1;
	D3Dpp.BackBufferFormat						= D3DFMT_X8R8G8B8;
	D3Dpp.BackBufferHeight						= height;
	D3Dpp.BackBufferWidth						= width;
	D3Dpp.SwapEffect							= D3DSWAPEFFECT_DISCARD;
	D3Dpp.PresentationInterval					= bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;
	D3Dpp.Flags									= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	D3Dpp.FullScreen_RefreshRateInHz			= window ? 0 : D3DPRESENT_RATE_DEFAULT;
	D3Dpp.MultiSampleQuality					= 0;
	D3Dpp.MultiSampleType						= D3DMULTISAMPLE_NONE;

	DWORD deviceBehaviorFlags = 0;

	pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &D3DCaps);

	if(D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}else
	{
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if(D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;
	}

	pD3DObject->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		deviceBehaviorFlags,
		&D3Dpp,
		&pD3DDevice);

	D3DXCreateSprite(pD3DDevice, &pD3DSprite);
	


}

pDevice	Engine::DX::getDevice()
{
	return pD3DDevice;
}

pSprite Engine::DX::getSprite()
{
	return pD3DSprite;
}

void Engine::DX::shutdown()
{
	SAFE_RELEASE(pD3DSprite);
	SAFE_RELEASE(pD3DObject);
	SAFE_RELEASE(pD3DDevice);
}

bool Engine::DX::DeviceIsLost()
{
	//Get the state of the graphics device
	HRESULT hr = pD3DDevice->TestCooperativeLevel();

	switch(hr)
	{
	case D3DERR_DEVICELOST:
		//Device is lost and cannot be reset yet:
		//Sleep awhile and try again next message loop cycle
		Sleep(20); //.02 seconds
		return true;

	case D3DERR_DRIVERINTERNALERROR:
		//Driver error: exit!
		MessageBox(m_hWnd, L"Internal Driver Error", L"DeviceIsLost()", MB_ICONSTOP);
		PostQuitMessage(0);
		return true;

	case D3DERR_DEVICENOTRESET:
		//device is lost but can be reset and restored
		
		OnResetDevice();
		return false;
	}
	return false;
}


void Engine::DX::OnResetDevice()
{
	HRESULT hr = pD3DDevice->Reset(&D3Dpp);
	if(FAILED(hr))
	{
		//TODO: Post fail message
	}

	//TODO: Reset aspect ratio on camera, rebuild projection matrix
}

void Engine::DX::OnReset(const long width, const long height)
{
	D3Dpp.BackBufferHeight = (UINT)height;
	D3Dpp.BackBufferWidth = (UINT)width;


	OnResetDevice();
}

void Engine::DX::fullscreen()
{
	window = false;
	D3Dpp.Windowed = window;
	D3Dpp.FullScreen_RefreshRateInHz			= window ? 0 : D3DPRESENT_RATE_DEFAULT;
	OnResetDevice();
}

void Engine::DX::windowed()
{
	window = true;
	D3Dpp.Windowed = window;
	D3Dpp.FullScreen_RefreshRateInHz			= window ? 0 : D3DPRESENT_RATE_DEFAULT;
	OnResetDevice();
}

bool Engine::DX::isWindowed()
{
	return window;
}