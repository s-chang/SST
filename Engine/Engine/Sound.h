#pragma once

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <string>
#include <iostream>
#include <vector>

typedef FMOD::Sound* pFSound;
typedef FMOD::System* pFSystem;
typedef FMOD::Channel* pFChannel;


namespace Engine
{
	class Sound
	{
	private:
		struct Storage
		{
			pFSound sound;
			std::string handle;
			bool playing;
		};

		std::vector<Storage>		songs;
		std::vector<Storage>		sound_effects;
		

		FMOD_RESULT					m_result;
		unsigned int				m_nVersion;	
		int							m_nNum_drivers;
		FMOD_SPEAKERMODE			m_speakermode;
		FMOD_CAPS					m_caps;
		char						m_cName[256];

		pFSystem					system;
		pFChannel					musicChannel;

		//pFSound						sound;

		Sound();
		~Sound();

		/**
		Name:			ERRCHECK
		Parameters:		FMOD_RESULT
		Return:			bool
		Description:	Checks FMOD processes for errors.
		*/
		bool ERRCHECK(FMOD_RESULT result);

	
		/**
		Name:			createStream
		Parameters:		Storage &storage - a container for sound and handle
						const std::string filename
		Return:			void
		Description:	A helper function used to create a Stream.
		*/
		void createStream(Storage &storage, const std::string filename);

		/**
		Name:			createSound
		Parameters:		Storage &storage - a container for sound and handle
						const std::string filename
		Return:			void
		Description:	A helper function used to create a Sound.
		*/
		void createSound(Storage &storage, const std::string filename);

		/**
		Name:			load
		Parameters:		none
		Return:			void
		Description:	A helper function used to load sounds.
		*/
		void load();

	public:
		static Sound* instance();


		/**
		Name:			init
		Parameters:		none
		Return:			void
		Description:	Initializes FMOD
		*/
		void init();

		/**
		Name:			update
		Parameters:		none
		Return:			void
		Description:	Updates FMOD
		*/
		void update();

		/**
		Name:			playStream
		Parameters:		const std::string handle - the handle to the stream being played
		Return:			void
		Description:	Plays the stream corresponding to the handle.
		*/
		void playStream(const std::string handle);

		/**
		Name:			playSound
		Parameters:		const std::string handle - the handle to the sound being played
		Return:			void
		Description:	Plays the sound corresponding to the handle.
		*/
		void playSound(const std::string handle);

		/**
		Name:			stopStream
		Parameters:		none
		Return:			void
		Description:	Stops the sound or stream being played.
		*/
		void stopStream();

		/**
		Name:			shutdown
		Parameters:		none
		Return:			void
		Description:	Shutdown FMOD and release memory.
		*/
		void shutdown();
	};


};
