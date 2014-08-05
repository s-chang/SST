#include "Mesh.h"
#include "DX.h"
#include "Macros.h"

Mesh::Mesh()
{
	mesh = NULL;
	mat_buffer = NULL;
	effect = NULL;
	materials.clear();
	textures.clear();
}

Mesh::~Mesh()
{
	shutdown();
}

void Mesh::loadTexturedMesh(LPCWSTR filename, pBuffer adjBuffer)
{
	pDevice device = Engine::DX::instance()->getDevice();
	D3DXLoadMeshFromX( filename, 
						D3DXMESH_MANAGED, 
						device, 
						&adjBuffer, 
						&mat_buffer, 
						&effect,
						&numMaterials, 
						&mesh);


	//Pull material (including texture) information from loaded .x file
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)mat_buffer->GetBufferPointer();

	D3DMATERIAL9* mesh_material = new D3DMATERIAL9[numMaterials];
	LPDIRECT3DTEXTURE9* meshTextures = new LPDIRECT3DTEXTURE9[numMaterials];

	for(DWORD i = 0; i <numMaterials; ++i)
	{
		//Copy the material
		mesh_material[i] = d3dxMaterials[i].MatD3D;

		//Set the ambient color (if needed) for the material (D3DX doesn't do this)
		mesh_material[i].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		//Create the texture if it exists - it may not
		meshTextures[i] = NULL;

		if(d3dxMaterials[i].pTextureFilename)
		{
			//Need to convert the texture filenames to Unicode string
			int len = 0;
			len = (int)strlen(d3dxMaterials[i].pTextureFilename) + 1;
			wchar_t *ucString = new wchar_t[len];
			mbstowcs(ucString, d3dxMaterials[i].pTextureFilename, len);
			LPCWSTR newfilename = (LPCWSTR)ucString;

			//Load the texture now that we have a valid filename

			D3DXCreateTextureFromFile(device, newfilename, &meshTextures[i]);
		
			delete[]ucString;
		}
	}
	for(unsigned int i = 0; i < numMaterials; i++){
		materials.push_back(mesh_material[i]);
	}
	for(unsigned int i = 0; i < numMaterials; i++){
		textures.push_back(meshTextures[i]);
	}
	delete [] mesh_material;
	delete [] meshTextures;
}

void Mesh::loadMesh(LPCWSTR filename, pBuffer adjBuffer)
{
	pDevice device = Engine::DX::instance()->getDevice();
	D3DXLoadMeshFromX(filename, 
						D3DXMESH_MANAGED, 
						device, 
						&adjBuffer,
						&mat_buffer,
						&effect, 
						&numMaterials, 
						&mesh);

	// Pull material (including texture) information from loaded .x file
	D3DXMATERIAL *d3dxMaterials = (D3DXMATERIAL*)mat_buffer->GetBufferPointer();

	D3DMATERIAL9* mesh_material = new D3DMATERIAL9[numMaterials];

	for(DWORD i = 0; i < numMaterials; ++i)
	{
		//Copy the material
		mesh_material[i] = d3dxMaterials[i].MatD3D;

		//Set the ambient color (if needed) for the material (D3DX doesn't do this)
		mesh_material[i].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
				
	}

	for(unsigned int i = 0; i < numMaterials; i++){
		materials.push_back(mesh_material[i]);
	}

	delete [] mesh_material;
}


pMesh Mesh::getMesh()
{
	return mesh;
}

DWORD Mesh::getNumMaterials()
{
	return numMaterials;
}

std::vector<D3DMATERIAL9> Mesh::getMeshMaterial()
{
	return materials;
}

std::vector<LPDIRECT3DTEXTURE9> Mesh::getMeshTexture()
{
	return textures;
}

void Mesh::shutdown()
{
	/*materials.clear();
	textures.clear();
	SAFE_RELEASE(effect);
	SAFE_RELEASE(mat_buffer);
	SAFE_RELEASE(mesh);*/
}