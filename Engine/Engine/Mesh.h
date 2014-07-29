#pragma once
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "winmm.lib")

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef ID3DXMesh* pMesh;
typedef ID3DXBuffer* pBuffer;
typedef D3DMATERIAL9* pMaterial;
typedef LPDIRECT3DTEXTURE9* pTexture;

class Mesh
{
private:
	pMesh			mesh;
	pBuffer			mat_buffer;
	pBuffer			effect;
	DWORD			numMaterials;
	pMaterial		mesh_material;
	pTexture		meshTexture;

public:
	Mesh();
	~Mesh();

	void loadMap(LPCWSTR filename, pBuffer adjBuffer);

	void loadCharacterMesh(LPCWSTR filename, pBuffer adjBuffer);

	pMesh getMesh();
	DWORD getNumMaterials();
	pMaterial getMeshMaterial();
	pTexture getMeshTexture();

	void shutdown();


};