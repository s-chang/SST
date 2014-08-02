#include "Mesh.h"
#include "DX.h"
#include "Macros.h"

Mesh::Mesh()
{
	mesh = nullptr;
	mat_buffer = nullptr;
	effect = nullptr;
	mesh_material = nullptr;
	meshTexture = nullptr;
}

Mesh::~Mesh()
{
}

void Mesh::loadMap(LPCWSTR filename, pBuffer adjBuffer)
{
	D3DXLoadMeshFromX( filename,
						D3DXMESH_MANAGED,
						Engine::DX::instance()->getDevice(),
						&adjBuffer,
						&mat_buffer,
						&effect,
						&numMaterials,
						&mesh);


	//pull material(including texture) information from loaded .x file
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)mat_buffer->GetBufferPointer();

	mesh_material = new D3DMATERIAL9[numMaterials];
	meshTexture = new LPDIRECT3DTEXTURE9[numMaterials];

	for(DWORD i = 0; i < numMaterials; ++i)
	{
		//Copy the material
		mesh_material[i] = d3dxMaterials[i].MatD3D;

		//Set the ambient color (if needed) for the material
		mesh_material[i].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		//Create the texture if it exists - it may not
		meshTexture[i] = NULL;

		if(d3dxMaterials[i].pTextureFilename)
		{
			//Need to convert the texture filenames to Unicode string
			int len = 0;
			len = (int)strlen(d3dxMaterials[i].pTextureFilename) + 1;
			wchar_t *ucString = new wchar_t[len];
			mbstowcs(ucString, d3dxMaterials[i].pTextureFilename, len);
			LPCWSTR newfilename = (LPCWSTR)ucString;

			//Load the texture
			D3DXCreateTextureFromFile(Engine::DX::instance()->getDevice(), newfilename, &meshTexture[i]);

		}
	}

}

void Mesh::loadCharacterMesh(LPCWSTR filename, pBuffer adjBuffer)
{
	D3DXLoadMeshFromX(filename, 
						D3DXMESH_MANAGED, 
						Engine::DX::instance()->getDevice(), 
						&adjBuffer,
						&mat_buffer,
						&effect, 
						&numMaterials, 
						&mesh);

	// Pull material (including texture) information from loaded .x file
	D3DXMATERIAL *d3dxMaterials = (D3DXMATERIAL*)mat_buffer->GetBufferPointer();

	mesh_material = new D3DMATERIAL9[numMaterials];

	for(DWORD i = 0; i < numMaterials; ++i)
	{
		//Copy the material
		mesh_material[i] = d3dxMaterials[i].MatD3D;

		//Set the ambient color (if needed) for the material (D3DX doesn't do this)
		mesh_material[i].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
				
	}
	
}

pMesh Mesh::getMesh()
{
	return mesh;
}

DWORD Mesh::getNumMaterials()
{
	return numMaterials;
}

pMaterial Mesh::getMeshMaterial()
{
	return mesh_material;
}

pTexture Mesh::getMeshTexture()
{
	return meshTexture;
}

void Mesh::shutdown()
{
	SAFE_RELEASE(effect);
	SAFE_RELEASE(mat_buffer);
	SAFE_RELEASE(mesh);

	if(mesh_material)
	{
		delete mesh_material;
		mesh_material = nullptr;
	}

	if(meshTexture)
	{
		delete meshTexture;
		meshTexture = nullptr;
	}
}