#pragma once
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "winmm.lib")

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <vector>

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
	
	std::vector<D3DMATERIAL9> materials;
	std::vector<LPDIRECT3DTEXTURE9> textures;

	DWORD			numMaterials;

public:
	Mesh();
	~Mesh();
	
	void loadTexturedMesh(LPCWSTR filename, pBuffer adjBuffer);
	void loadMesh(LPCWSTR filename, pBuffer adjBuffer);

	pMesh getMesh();
	DWORD getNumMaterials();
	std::vector<D3DMATERIAL9> getMeshMaterial();
	std::vector<LPDIRECT3DTEXTURE9> getMeshTexture();

	void shutdown();

};