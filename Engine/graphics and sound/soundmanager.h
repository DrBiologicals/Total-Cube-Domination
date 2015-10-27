// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   soundmanager.h
//  Description :   Declaration for CSoundManager
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_SOUNDMANAGER_H__
#define __IGFEB10_MODULE_SOUNDMANAGER_H__

// Library Includes
#include <d3dx9.h>
#include <d3d9.h>
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

// Local Includes
#include "sound.h"

// Types
const uint32 MAX_SOUNDS = 64;
const uint32 MAX_CHANNELS = 156;

enum ESoundChannel
{
	SOUNDCHANNEL_SFX,
	SOUNDCHANNEL_MUSIC,
	SOUNDCHANNEL_ALL
};

enum ESoundType
{
	SOUNDTYPE_SFX,
	SOUNDTYPE_MUSIC
};

// Prototypes

class CSoundManager
{
	// Member Functions
public:
	bool Initialise();
	void Clear();

	uint32 CreateSound(const int8* _kpcFileName, float32 _fVolume=1.0f, bool _bMusic=false, float32 _fMaxDist=50.0f);
	CSound* GetSound(uint32 _uiID);

	void PlaySound(uint32 _uiID);
	void PlaySoundFromPoint(uint32 _uiID, D3DXVECTOR3& _vec3, float32 _fSoundMod=1.0f);

	void SetChannelPause(bool _bPause, ESoundChannel _eChannel);

	static CSoundManager& GetInstance();
	static void DestroyInstance();

protected:

private:

	CSoundManager();
	CSoundManager(const CSoundManager& _kr);
	~CSoundManager();

	CSoundManager& operator =(const CSoundManager& _kr);

	// Member Variables
public:

protected:
	FMOD::System* m_pSystem;
	CSound* m_apSound[MAX_SOUNDS];

	uint32 m_uiSoundTotal;
	float32 m_fMusicVolume;

	FMOD::Channel* m_pMusicChannel;
	FMOD::Channel* m_pSFXChannel;
private:
	static CSoundManager* s_pInstance;
	static FMOD_MODE s_soundModeDefault;
}; 

#endif // __IGFEB10_MODULE_SOUNDMANAGER_H__

/*
to use FMOD, in Visual Studio 2005:
Projects and Solutions > VC++ Directories
Include files: C:\Program Files\FMOD SoundSystem\FMOD Programmers API Win32\api\inc
Library files: C:\Program Files\FMOD SoundSystem\FMOD Programmers API Win32\api\lib
*/