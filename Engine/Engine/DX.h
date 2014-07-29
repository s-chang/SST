/**
Written by:  Smyth Chang
Description:  The DX class initializes DirectX for use

*/
#pragma once

#pragma comment(lib, "winmm.lib")

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Macros.h"

typedef IDirect3D9* pObject;
typedef IDirect3DDevice9* pDevice;
typedef ID3DXSprite* pSprite;
typedef D3DCAPS9 CAPS;
typedef D3DPRESENT_PARAMETERS PRESENT_PARA;

namespace Engine
{
	class DX
	{
	private:
		bool		bVsync;
		bool		window;
		HWND		m_hWnd;

		pObject		pD3DObject;
		pDevice		pD3DDevice;
		CAPS		D3DCaps;

		pSprite		pD3DSprite;

		PRESENT_PARA D3Dpp;

		DX();

	public:
		~DX();

		//Return IDirect3DDevice9* device
		pDevice getDevice();

		//Return ID3DXSprite* object
		pSprite getSprite();

		//Return the only instance of DX
		static DX* instance();


		/**
		Name:		init
		Parameters:	HWND &hWnd - the handle to the window
					bool a_window - window or fullscreen
		Return:		void
		Description: Initializes DirectX for use
		*/
		void init(HWND &hWnd, bool a_window);

		/**
		Name:		shutdown
		Parameters:	none
		Return:		void
		Descritpion: Release directX objects from memory and shutdown
		*/
		void shutdown();

		/**
		Name:		DeviceIsLost
		Parameters:	None
		Return:		bool
		Description: Checks to see if the device is lost.
		*/
		bool DeviceIsLost();

		/**
		Name:		OnResetDevice
		Parameters:	none
		Return:		void
		Description: Reset the device
		*/
		void OnResetDevice();

		/**
		Name:		OnReset
		Parameters: const long width - the width of the window
					const long height - the height of the window
		Return:		void
		Description: Changes the height/width of the window
		*/
		void OnReset(const long width, const long height);

		/**
		Name:		fullscreen
		Parameters: none
		Return:		void
		Description: switch to fullscreen
		*/
		void fullscreen();

		/**
		Name:		windowed
		Parameters: none
		Return:		void
		Description:	switch to windowed
		*/
		void windowed();

		bool isWindowed();
	};

};