// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   sound.cpp
//  Description :   sound.cppfor implementation of sound.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../entity structures/player objects/playermanager.h"
#include "../../entity structures/player objects/tank.h"
#include "../../entity structures/player objects/player.h"

// This Includes
#include "sound.h"

// Static Variables
FMOD_MODE CSound::s_soundModeDefault = FMOD_2D | FMOD_SOFTWARE;
FMOD::System* CSound::s_pSystem = 0;
bool CSound::s_bDistModifier = true;

// Static Function Prototypes

// Implementation
CSound::CSound()
: m_pFMODSound(0)
, m_fVolume(0)
, m_ppChannel(0)
, m_bMusic(false)
, m_fMaxDist(0.0f)
{
	
}

CSound::~CSound()
{
	m_pFMODSound->release();
	m_pFMODSound = 0;
	m_ppChannel = 0;
}

/**
* Initialises CSound, and creates the FMOD::Sound object.
*
* @author				Cameron MacIntosh
* @param _kpcFileName	the filename of the sound to load
* @param _fVolume		the maximum volume the sound should be set to
* @param _bMusic		if the sound is music (and not sfx, etc.)
* @param _fMaxDist		the maximum distance a human-controlled tank can be from a sound before
*							the sound is silent.
* @return				if the initialisation succeeded.
**/
bool CSound::Initialise(const int8 *_kpcFileName, FMOD::Channel* _ppChannel, float32 _fVolume, bool _bMusic, float32 _fMaxDist)
{
	if(s_pSystem!=0)
	{
		m_ppChannel = _ppChannel;
		m_fVolume = _fVolume;
		m_bMusic = _bMusic;
		m_fMaxDist = _fMaxDist;
		
		FMOD_MODE soundMode = s_soundModeDefault;
		if(m_bMusic)
		{
			soundMode |= FMOD_LOOP_NORMAL | FMOD_CREATECOMPRESSEDSAMPLE | FMOD_UNIQUE;
		}
		
		s_pSystem->createSound(_kpcFileName, soundMode, 0, &m_pFMODSound);
		s_pSystem->update();
		m_ppChannel->setVolume(m_fVolume);

		return true;
	}
	return false;
}

/**
* Plays a sound at full volume
*
* @author				Cameron MacIntosh
**/
void CSound::PlaySound()
{
	if(s_pSystem!=0)
	{
		s_pSystem->playSound(FMOD_CHANNEL_FREE, m_pFMODSound, false, &m_ppChannel);
		s_pSystem->update();
		m_ppChannel->setVolume(m_fVolume);
	}
}

/**
* Plays a sound at a volume responding to the distance from the sound's origin.
*
* @author				Cameron MacIntosh
* @param _vec3			the origin position of the sound
* @param _fSoundMod		percentage of the resulting sound that will play
**/
void CSound::PlaySoundFromPoint(D3DXVECTOR3& _vec3, float32 _fSoundMod)
{
	if(s_pSystem!=0)
	{
		if(s_bDistModifier)
		{
			//check for distance to human players
			float32 fDist = GetDistance(_vec3);
			if(fDist<m_fMaxDist)
			{
				s_pSystem->playSound(FMOD_CHANNEL_FREE, m_pFMODSound, false, &m_ppChannel);
				s_pSystem->update();
				m_ppChannel->setVolume(m_fVolume*(m_fMaxDist-fDist)/m_fMaxDist*_fSoundMod);
			}
		}
		else
		{
			s_pSystem->playSound(FMOD_CHANNEL_FREE, m_pFMODSound, false, &m_ppChannel);
			s_pSystem->update();
			m_ppChannel->setVolume(m_fVolume*_fSoundMod);
		}
	}
}

/**
* Returns the closest distance to a human player
*
* @author				Cameron MacIntosh
* @param _vec3Origin	the origin of the sound
* @return				the closest distance
**/
float32 CSound::GetDistance(D3DXVECTOR3& _vec3Origin)
{
	D3DXVECTOR3 vec3(0.0f,0.0f,0.0f);
	float32 fClosestDist = 0.0f;
	float32 fCurrDist = 0.0f;

	const D3DXVECTOR3* vec3Tank = 0;
	CPlayer* pPlayer;
	for(uint32 i=0; i<8; ++i)
	{
		pPlayer = CPlayerManager::GetPlayerManagerInstance().GetPlayer(i);
		if(pPlayer->IsHuman())
		{
			const D3DXVECTOR3* vec3Tank = &pPlayer->GetTank()->GetPosition();
			vec3 = _vec3Origin - (*vec3Tank);

			fCurrDist = D3DXVec3Length(&vec3);
			if((fClosestDist>fCurrDist)||(fClosestDist==0))
			{
				fClosestDist = fCurrDist;
			}
		}
	}

	//return the closest distance
	return(fClosestDist);
}

/**
* sets the maximum distance that the sound can be heard from
*
* @author				Cameron MacIntosh
* @param _fDistance		the maximum distance
**/
void CSound::SetMaxDistance(float32 _fDistance)
{
	m_fMaxDist = _fDistance;
}

/**
* sets the static system pointer
*
* @author				Cameron MacIntosh
* @param _pSystem		a pointer to the FMOD::System used
**/
bool CSound::SetSystem(FMOD::System* _pSystem)
{
	if(_pSystem==0)
	{
		return false;
	}
	s_pSystem = _pSystem;
	return true;
}