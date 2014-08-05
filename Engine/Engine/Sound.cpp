#include "Sound.h"
#include "Macros.h"
#include <fstream>

Engine::Sound::Sound()
{
	songs.clear();
	sound_effects.clear();

	system = nullptr;
	musicChannel = nullptr;

}

Engine::Sound::~Sound()
{}

Engine::Sound *Engine::Sound::instance()
{
	static Sound Sound;
	return &Sound;
}

void Engine::Sound::init()
{
	m_result = FMOD::System_Create(&system);
	ERRCHECK(m_result);

	musicChannel->setVolume(0.3f);

	//Set FMOD version
	m_result = system->getVersion(&m_nVersion);
	ERRCHECK(m_result);

	if(m_nVersion < FMOD_VERSION)
	{
		printf("Error! You are using an old version of FMOD %08x.  This program requires %98x\n",
			m_nVersion, FMOD_VERSION);
		
	}
	
	//Set drivers
	m_result = system->getNumDrivers(&m_nNum_drivers);
	ERRCHECK(m_result);

	if(m_nNum_drivers == 0)
	{
		m_result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ERRCHECK(m_result);
	}
	else
	{
		//Set speaker mode
		m_result = system->getDriverCaps(0, &m_caps, NULL, &m_speakermode);
		ERRCHECK(m_result);

		m_result = system->setSpeakerMode(m_speakermode);
		ERRCHECK(m_result);

		//Set Driver Info
		if(m_caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			m_result = system->setDSPBufferSize(1024,10);
			ERRCHECK(m_result);
		}

		m_result = system->getDriverInfo(0, m_cName, 256, 0);
		ERRCHECK(m_result);

		if(strstr(m_cName, "SigmaTel"))
		{
			m_result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0,
				FMOD_DSP_RESAMPLER_LINEAR);
			ERRCHECK(m_result);
		}
	}
	//Check sound support
	m_result = system->init(10, FMOD_INIT_NORMAL, 0);

	if(m_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		m_result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		ERRCHECK(m_result);

		m_result = system->init(10, FMOD_INIT_NORMAL, 0);

	}
	ERRCHECK(m_result);

	load();


	
}


void Engine::Sound::createStream(Storage &storage, const std::string filename)
{
	m_result = system->createStream(filename.c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &storage.sound);
	ERRCHECK(m_result);
	
}

void Engine::Sound::createSound(Storage &storage, const std::string filename)
{
	
	m_result = system->createStream(filename.c_str(), FMOD_DEFAULT, 0, &storage.sound);
	ERRCHECK(m_result);
	
}

void Engine::Sound::load()
{
	//Temporary storage to load to storage vector
	Storage temp_Storage;

	//Temporary variables to hold data
	std::string temp_handle;
	std::string temp_file_name;
	
	//Temporary struct to hold data
	struct temp_Data
	{
		std::string temp_handle;
		std::string temp_file_name;
	};

	//Temporary vector to transfer data
	std::vector<temp_Data> tempStorageData;

	
	std::ifstream file("SoundEffects.txt");

	while(!file.eof())
	{
		//store file name and handle to temp variables
		file >> temp_file_name >> temp_handle;

		//create a temporary struct to hold data
		temp_Data some_data;
		some_data.temp_handle = temp_handle;
		some_data.temp_file_name = temp_file_name;

		//push back the data
		tempStorageData.push_back(some_data);
		
	}
	//end of file, close file
	file.close();
	
	//iterate through temp data storage to create sound effects
	for(unsigned int i = 0; i < tempStorageData.size(); i++)
	{
		
		//Transfer temp_data to storage
		temp_Storage.handle = tempStorageData[i].temp_handle;
		temp_Storage.playing = false;
		
		//Create Sound Effect
		createSound(temp_Storage, tempStorageData[i].temp_file_name);

		//Push temp_storage into sound effect storage container
		sound_effects.push_back(temp_Storage);
		//Clear memory for next file
		temp_Storage.sound = nullptr;
	}

	//Repeat for Streams
	std::ifstream file2("BGM.txt");

	while(!file2.eof())
	{
		//store file name and handle to temp variables
		file2 >> temp_file_name >> temp_handle;

		//create a temporary struct to hold data
		temp_Data some_data;
		some_data.temp_handle = temp_handle;
		some_data.temp_file_name = temp_file_name;

		//push back the data
		tempStorageData.push_back(some_data);
		
	}
	//end of file, close file
	file2.close();
	
	//iterate through temp data storage to create songs
	for(unsigned int i = 0; i < tempStorageData.size(); i++)
	{
		
		//Transfer temp_data to storage
		temp_Storage.handle = tempStorageData[i].temp_handle;
		temp_Storage.playing = false;
		
		//Create Sound Effect
		createSound(temp_Storage, tempStorageData[i].temp_file_name);

		//Push temp_storage into song storage container
		songs.push_back(temp_Storage);
		//Clear memory for next file
		temp_Storage.sound = nullptr;
	}
	

}

void Engine::Sound::update()
{
	m_result = system->update();
	ERRCHECK(m_result);
}

bool Engine::Sound::ERRCHECK(FMOD_RESULT result)
{
	if(result != FMOD_OK)
		return false;	//TODO: RETURN ERRORCODE
	return true;
}

void Engine::Sound::playStream(const std::string handle)
{
	//find if the stream exists
	//TODO: use a better search algorithm
	for(unsigned int i = 0; i < songs.size(); i++)
	{
		if(handle == songs[i].handle)
		{
			if(!songs[i].playing)
			{
				m_result = system->playSound(FMOD_CHANNEL_FREE, songs[i].sound, false, &musicChannel);
				ERRCHECK(m_result);
				songs[i].playing = true;
			}
		}
	}

	//TODO: throw exception if there is no song found

}

void Engine::Sound::playSound(const std::string handle)
{
	//find if the song exists
	//TODO: use a better search algorithm
	for(unsigned int i = 0; i < songs.size(); i++)
	{
		if(handle == sound_effects[i].handle)
		{
			if(!sound_effects[i].playing)
			{
				m_result = system->playSound(FMOD_CHANNEL_FREE, sound_effects[i].sound, false, &musicChannel);
				ERRCHECK(m_result);
				sound_effects[i].playing = true;
			}
		}else
		{
			sound_effects[i].playing = false;
		}
	}

	//TODO: throw exception if there is no song found
	
}

void Engine::Sound::stopStream()
{
	m_result = musicChannel->stop();
	ERRCHECK(m_result);

}

void Engine::Sound::shutdown()
{
	songs.clear();
	sound_effects.clear();

	musicChannel = nullptr;
	SAFE_RELEASE2(system);

}