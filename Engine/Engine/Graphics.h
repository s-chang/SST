/**
Written by:  Smyth Chang
Description:  The graphics class handles all of the drawing to the screen.

*/
#pragma once
#include "Drawable.h"

#include <vector>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef IDirect3DTexture9* pTexture;
typedef D3DXIMAGE_INFO iInfo;

namespace Engine
{
	class Graphics
	{
	private:
		struct Storage
		{
			pTexture texture;
			iInfo	info;
			std::string handle;		
		};

		pTexture error;
		iInfo errorinfo;

		std::vector<Storage> storage;

		Graphics();
		void load();
		pTexture getTexture(const std::string handle);
		iInfo getInfo(const std::string handle);

	public:
		~Graphics();

		/**
		Name:		instance
		Parameters: none
		Return:		Graphics
		Description: Returns the only instance of Graphics
		*/
		static Graphics* instance();

		/**
		Name:		init
		Parameters:	none
		Return:		void
		Description: initializes the graphics class
		*/
		void init();

		/**
		Name:		render
		parameters:	Drawable object
		Return:		void
		Description: Renders the Drawable object to the screen
		*/
		void render(Drawable object);

		/**
		Name:		shutdown
		Parameters: none
		Return:		void
		Description: Release pointer objects from memory.
		*/
		void shutdown();
		
	};
};
