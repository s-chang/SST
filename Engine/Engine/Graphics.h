/**
Written by:  Smyth Chang
Description:  The graphics class handles all of the drawing to the screen.

*/
#pragma once
#include "Drawable.h"

#include <vector>
#include <string>
#include <hash_map>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

typedef IDirect3DTexture9* pDirectTexture;
typedef D3DXIMAGE_INFO iInfo;


namespace Engine
{
	class Graphics
	{
	private:
		struct Storage
		{
			pDirectTexture texture;
			iInfo	info;
			std::string handle;		
		};
		
		pDirectTexture error;
		iInfo errorinfo;

		std::vector<Storage> storage;	
		
		void load();
		
		pDirectTexture getTexture(const std::string handle);
		iInfo getInfo(const std::string handle);


		struct MeshStorage
		{
			Mesh mesh;
			std::string handle;
		};

		std::vector<MeshStorage> meshStorage;
		Mesh* getMesh(const std::string handle);
		void loadMesh();
		pBuffer adjBuffer;
		
		Camera camera;
		Light light;

		ID3DXBuffer*	m_EffectError;
		ID3DXEffect*	m_Effect;
		D3DXHANDLE		m_tech;

		Graphics();
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
