// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   sound.h
//  Description :   Declaration for Csound
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_SOUND_H__
#define __IGFEB10_MODULE_SOUND_H__

// Library Includes
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

// Local Includes

// Types

// Prototypes

class CSound
{
	// Member Functions
public:
	CSound();
	~CSound();

	bool Initialise(const int8 *_kpcFileName, FMOD::Channel* _ppChannel, float32 _fVolume, bool _bMusic, float32 _fMaxDist);

	void PlaySound();
	void PlaySoundFromPoint(D3DXVECTOR3& _vec3, float32 _fSoundMod=1.0f);
	float32 GetDistance(D3DXVECTOR3& _vec3Origin);

	void SetMaxDistance(float32 _fDistance);

	static bool SetSystem(FMOD::System* _pSystem);

protected:

private:

	// Member Variables
public:

protected:
	FMOD::Sound* m_pFMODSound;
	float32 m_fVolume;
	FMOD::Channel* m_ppChannel;
	bool m_bMusic;
	float32 m_fMaxDist;
private:
	static FMOD_MODE s_soundModeDefault;
	static FMOD::System* s_pSystem;
	static bool s_bDistModifier;
}; 

#endif // __IGFEB10_MODULE_SOUND_H__

