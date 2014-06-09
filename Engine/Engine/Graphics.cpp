#include "Graphics.h"
#include <fstream>
#include "DX.h"

//helper function
std::wstring string2wstring( const std::string word)
{
	int length;
	int slength = (int)word.length() + 1;
	length = MultiByteToWideChar(CP_ACP, 0, word.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, word.c_str(), slength, buf, length);
	std::wstring wWord(buf);
	delete[] buf;
	return wWord;
}

Engine::Graphics::Graphics()
{}

Engine::Graphics::~Graphics()
{}

Engine::Graphics* Engine::Graphics::instance()
{
	static Graphics instance;
	return &instance;
}

void Engine::Graphics::init()
{
	load();
}

void Engine::Graphics::render(Drawable object)
{
	D3DXMATRIX transMat, scaleMat, rotMat, worldMat;

	D3DXMatrixIdentity(&transMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&worldMat);

	D3DXMatrixScaling(&scaleMat, object.getScale().x, object.getScale().y, object.getScale().z);
	D3DXMatrixTranslation(&transMat, object.getTranslate().x, object.getTranslate().y, object.getTranslate().z);
	D3DXMatrixRotationYawPitchRoll(&rotMat, D3DXToRadian(object.getRotate().y),D3DXToRadian(object.getRotate().x), D3DXToRadian(object.getRotate().z));
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
	D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

	if(!object.get3D())
	{
		Engine::DX::instance()->getSprite()->SetTransform(&worldMat);
		
		Engine::DX::instance()->getSprite()->Draw(
			getTexture(object.getHandle()),
			object.getIsSpriteSheet() ? &object.getRect() : 0,
			object.getIsSpriteSheet() ? &dVec3(object.getWidth() * 0.5f, object.getHeight() * 0.5f, 0.0f) : &dVec3(getInfo(object.getHandle()).Width *0.5f, getInfo(object.getHandle()).Height *0.5f, 0.0f),
			0,
			object.getColor());
	}

	if(object.get3D())
	{
		
	}
}

void Engine::Graphics::shutdown()
{
	for(unsigned int i = 0; i < storage.size(); i++)
	{
		SAFE_RELEASE(storage[i].texture);
		
	}
	storage.clear();
}

void Engine::Graphics::load()
{
	Storage temp_storage;

	std::string temp_file_name;
	std::string temp_handle;
	//LPCWSTR rFilename;
	
	struct temp_Data
	{
		std::string temp_handle;
		std::wstring temp_file_name;
	};

	std::vector<temp_Data> tempStorageData;

	//TODO: read from text file
	std::ifstream file("Textures2D.txt");
	//std::wstring wtemp;

	//read til end of file
	while(!file.eof())
	{
		//store file name and handle to the file in temp variables
		file >> temp_file_name >> temp_handle;

		//create a temporary struct to hold data
		
		temp_Data some_data;
		some_data.temp_file_name = L"";
		some_data.temp_handle = temp_handle;
		
		//convert string to LPCWSTR 
		some_data.temp_file_name = std::wstring(temp_file_name.begin(), temp_file_name.end());
		//LPCWSTR stemp = wtemp.c_str();
		//some_data.temp_file_name = stemp;
		//wtemp = string2wstring(temp_file_name);
		//some_data.temp_file_name = wtemp.c_str();
		

		//push back the data
		tempStorageData.push_back(some_data);
		
		
	}
	//end of file, close file
	file.close();

	//Iterate through temporary data storage to create textures
	for(unsigned int i = 0; i < tempStorageData.size(); i++)
	{
		D3DXCreateTextureFromFileEx(Engine::DX::instance()->getDevice(),
			tempStorageData[i].temp_file_name.c_str(), 0, 0, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
			D3DCOLOR_XRGB(255,255,255), &temp_storage.info, 0, &temp_storage.texture);
		temp_storage.handle = tempStorageData[i].temp_handle;

		storage.push_back( temp_storage );
		//set pointer to nullptr before reusing
		temp_storage.texture = nullptr;
	}
	
	//TODO sort storage

	//Create Error texture to show errors
	D3DXCreateTextureFromFileEx(Engine::DX::instance()->getDevice(),
			L"error.png", 0, 0, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
			D3DCOLOR_XRGB(255,255,255), &errorinfo, 0, &error);
	
}

pTexture Engine::Graphics::getTexture(const std::string handle)
{
	//TODO: use search algorithm
	for(unsigned int i = 0; i < storage.size(); i++)
	{
		if(handle == storage[i].handle)
			return storage[i].texture;
	}
	
	return error;
	//TODO: Throw error exception if no texture is found
}

iInfo Engine::Graphics::getInfo(const std::string handle)
{
	//TODO: use search algorithm
	for(unsigned int i = 0; i < storage.size(); i++)
	{
		if(handle == storage[i].handle)
			return storage[i].info;
	}
	//TODO: Throw error exception if no image information is found.
	return errorinfo;
}