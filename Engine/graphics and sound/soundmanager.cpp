// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   soundmanager.cpp
//  Description :   soundmanager.cppfor implementation of soundmanager.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../Totalcubedomination.h"

// This Includes
#include "soundmanager.h"

// Static Variables
CSoundManager* CSoundManager::s_pInstance = 0;
FMOD_MODE CSoundManager::s_soundModeDefault = FMOD_2D | FMOD_SOFTWARE;

// Static Function Prototypes

// Implementation

/**
* Constructor for CSoundManager
*
* @author	Cameron MacIntosh
**/
CSoundManager::CSoundManager()
: m_pSystem(0)
, m_pMusicChannel(0)
, m_pSFXChannel(0)
, m_uiSoundTotal(0)
, m_fMusicVolume(1.0f)
{
	ZeroMemory(m_apSound, sizeof(m_apSound));
	/*for(int32 i=0; i<MAX_SOUNDS; ++i)
	{
		m_apSounds[i] = 0;
	}*/
}

/**
* Deconstructor for CSoundManager
*
* @author	Cameron MacIntosh
**/
CSoundManager::~CSoundManager()
{
	if(m_pSystem)
	{
		Clear();
		m_pSystem->close();
		m_pSystem->release();
	}
}

/**
* Initialises CSoundManager. Readies the FMOD system.
*
* @author	Cameron MacIntosh
**/
bool
CSoundManager::Initialise()
{
	FMOD_RESULT result;
	//Create the FMOD system object
	result = FMOD::System_Create(&m_pSystem);
	
	if (FMOD_OK != result)
	{
		#ifdef _DEBUG
		//initialisation has failed
		CTotalCubeDomination::GetInstance().LogMessage("SoundManager initialisation FAILED on FMOD::System_Create", LOG_MESSAGE_SOUND);
		#endif // _DEBUG

		return false;
	}
	result = m_pSystem->init(MAX_CHANNELS, FMOD_INIT_NORMAL, NULL);
	if (FMOD_OK != result)
	{
		#ifdef _DEBUG
		//initialisation has failed
		CTotalCubeDomination::GetInstance().LogMessage("SoundManager initialisation FAILED on FMOD::System->init", LOG_MESSAGE_SOUND);
		#endif // _DEBUG

		return false;
	}

	m_pSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
	m_pSystem->setSoftwareChannels(100);
	m_pSystem->setHardwareChannels(32, 64, 32, 64);

	CSound::SetSystem(m_pSystem);

	#ifdef _DEBUG
	CTotalCubeDomination::GetInstance().LogMessage("SoundManager initialised", LOG_MESSAGE_SOUND);
	#endif // _DEBUG

	return true;
}

/**
* Creates a sound
*
* @author				Cameron MacIntosh
* @param _kpcFileName	the filename of the sound to load
* @param _fVolume		the maximum volume the sound should be set to
* @param _bMusic		if the sound is music (and not sfx, etc.)
* @param _fMaxDist		the maximum distance a human-controlled tank can be from a sound before
*							the sound is silent.
* @return				the new sound ID
**/
uint32
CSoundManager::CreateSound(const int8 *_kpcFileName, float32 _fVolume, bool _bMusic, float32 _fMaxDist)
{
	if(m_uiSoundTotal<MAX_SOUNDS)
	{
		m_apSound[m_uiSoundTotal] = new CSound();
		if(_bMusic)
		{
			m_apSound[m_uiSoundTotal]->Initialise(_kpcFileName, m_pMusicChannel, _fVolume, _bMusic, _fMaxDist);
		}
		else
		{
			m_apSound[m_uiSoundTotal]->Initialise(_kpcFileName, m_pSFXChannel, _fVolume, _bMusic, _fMaxDist);
		}
		++m_uiSoundTotal;
		return(m_uiSoundTotal-1);
	}
	return(BAD_ID);
}

/**
* Returns a pointer to the CSound object that corresponds to the passed in ID
*
* @author				Cameron MacIntosh
* @param _uiID			the ID number of the CSound object
* @return				a pointer to the CSound object that corresponds to the ID
**/
CSound*
CSoundManager::GetSound(uint32 _uiID)
{
	if(_uiID<MAX_SOUNDS)
	{
		return(m_apSound[_uiID]);
	}
	return(0);
}

/**
* Plays a sound at full volume
*
* @author				Cameron MacIntosh
* @param _uiID			the ID number of the sound
**/
void
CSoundManager::PlaySound(uint32 _uiID)
{
	if((MAX_SOUNDS>_uiID)&&(m_apSound[_uiID]))
	{
		m_apSound[_uiID]->PlaySoundA();
	}
}

/**
* Plays a sound at a volume responding to the distance from the sound's origin.
*
* @author				Cameron MacIntosh
* @param _uiID			the ID of the sound
* @param _vec3			the origin position of the sound
**/
void
CSoundManager::PlaySoundFromPoint(uint32 _uiID, D3DXVECTOR3& _vec3, float32 _fSoundMod)
{
	if((MAX_SOUNDS>_uiID)&&(m_apSound[_uiID]))
	{
		m_apSound[_uiID]->PlaySoundFromPoint(_vec3, _fSoundMod);
	}
}

/**
* clear all allocated resources from the sound manager
*
* @author Cameron MacIntosh
*/
void 
CSoundManager::Clear()
{
	for (int32 i = 0; i < MAX_SOUNDS; ++i)
	{
		delete m_apSound[i];
		m_apSound[i] = 0;
	}
}

/**
* returns a reference to the static instance of this class
*
* @author	Cameron MacIntosh
* @return	a reference to the static instance of this class
*/
CSoundManager&
CSoundManager::GetInstance()
{
	if(!s_pInstance)
	{
		s_pInstance = new CSoundManager();
		s_pInstance->Initialise();
	}
	return(*s_pInstance);
}

/**
* deletes the static instance of this class
*
* @author	Cameron MacIntosh
*/
void
CSoundManager::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}

/**
* pauses/unpauses a channel/ channels.
*
* @author				Cameron MacIntosh
* @param _bPause		whether to pause or unpause the channel
* @param _eChannel		the enum for which channel to affect
*/
void CSoundManager::SetChannelPause(bool _bPause, ESoundChannel _eChannel)
{
	switch(_eChannel)
	{
	case SOUNDCHANNEL_SFX:
		m_pSFXChannel->setPaused(_bPause);
		break;
	case SOUNDCHANNEL_ALL:
		m_pSFXChannel->setPaused(_bPause);
	case SOUNDCHANNEL_MUSIC:
		m_pMusicChannel->setPaused(_bPause);
		break;
	}
}