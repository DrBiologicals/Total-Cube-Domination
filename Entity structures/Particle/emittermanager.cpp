// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   emittermanager.cpp
//  Description :   emittermanager.cppfor implementation of emittermanager.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "explodeparticleemitter.h"
#include "flameparticleemitter.h"
#include "flagparticleemitter.h"
#include "spiralparticleemitter.h"
#include "picparticleemitter.h"
#include "../player objects/tank.h"
#include "../player objects/bullet.h"
#include "bulletwallparticles.h"

// This Includes
#include "emittermanager.h"

// Static Variables
CEmitterManager* CEmitterManager::s_pInstance = 0;

// Static Function Prototypes

// Implementation

CEmitterManager::CEmitterManager()
{
}

CEmitterManager::~CEmitterManager()
{
	for (std::list<CParticleEmitter*>::iterator iter = m_listEmitters.begin(); 
		iter != m_listEmitters.end(); ++iter)
    {
        delete (*iter);
    }
    m_listEmitters.clear();
}

bool
CEmitterManager::Initialise()
{
	return (true);
}

/*
* Clears the emittermanager
* @author Rigardt de Vries
* @return void
*/
void
CEmitterManager::Clear()
{
    for (std::list<CParticleEmitter*>::iterator iter = m_listEmitters.begin(); 
		iter != m_listEmitters.end(); ++iter)
    {
        delete (*iter);
    }
    m_listEmitters.clear();
}

/*
* GetEmitterManager
* @author Michael McQuarrie
* 
* @return CEmitterManager&
*/
CEmitterManager&
CEmitterManager::GetInstance()
{
	if(s_pInstance == 0)
	{
		s_pInstance = new CEmitterManager;
	}
	return (*s_pInstance);
}

/*
* DestroyInstance
* @author Michael McQuarrie
* 
* @return void
*/
void
CEmitterManager::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}

/*
* Process
* @author Michael McQuarrie
* @param _fDeltaTick
* @return void
*/
void
CEmitterManager::Process(float32 _fDeltaTick)
{
	for (std::list<CParticleEmitter*>::iterator iter = m_listEmitters.begin(); 
		iter != m_listEmitters.end();)
    {
		if (!(*iter)->IsAlive())
		{
			delete (*iter);
			iter = m_listEmitters.erase(iter);
		}
		else
		{
			++iter;
		}
    }
}

/*
* AddEmitter
* @author Michael McQuarrie / Rigardt de Vries
* @param _pEmitter
* @return void
*/
uint32
CEmitterManager::AddEmitter(int32 _iNumParticles, D3DXVECTOR3 _vec3Origin, EParticleType _eType, ETeam _eTeam, 
                            CFlameGrate* _pFlameGrate, CFlag* _pFlag, CTank* _pTank, CBullet* _pBullet)
{
	if (PARTICLE_EXPLODE == _eType)
	{
		CExplodeParticleEmitter* pEmitter = new CExplodeParticleEmitter;
		pEmitter->Initialise(_iNumParticles, _vec3Origin, _eTeam);
		m_listEmitters.push_back(pEmitter);
	}
	else if (PARTICLE_FLAME == _eType)
	{
		CFlameParticleEmitter* pEmitter = new CFlameParticleEmitter;
		pEmitter->Initialise(_iNumParticles, _vec3Origin, _pFlameGrate);
		m_listEmitters.push_back(pEmitter);
	}
	else if(PARTICLE_FLAG == _eType)
	{
		CFlagParticleEmitter* pEmitter = new CFlagParticleEmitter;
		pEmitter->Initialise(_iNumParticles, _vec3Origin, _pFlag);
		m_listEmitters.push_back(pEmitter);
	}
    else if (PARTICLE_SPIRAL == _eType)
    {
        CSpiralParticleEmitter* pEmitter = new CSpiralParticleEmitter;
		pEmitter->Initialise(_iNumParticles, _vec3Origin, _pTank);
		m_listEmitters.push_back(pEmitter);
    }
	else if (PARTICLE_BULLET_WALL == _eType)
	{
		CBulletWallParticles* pEmitter = new CBulletWallParticles;
		pEmitter->Initialise(_iNumParticles, _vec3Origin, _eType, _pBullet);
		m_listEmitters.push_back(pEmitter);
	}
	else if (PARTICLE_PIC == _eType)
	{
		CPICParticleEmitter* pEmitter = new CPICParticleEmitter;
		pEmitter->Initialise(_iNumParticles, _vec3Origin, _pTank);
		m_listEmitters.push_back(pEmitter);
	}
    return (static_cast<uint32>(m_listEmitters.size()) - 1);
}

/**
* 
* Removes the pointer held in the m_listEmitters at the position 
*	passed in. 
* If the index position does not exist, nothing happens.
* 
* @author Rebeccah Cox
* @param uint32 _uiID
* @return void
*/
void
CEmitterManager::RemoveEmitter(CParticleEmitter* _pEmitter)
{
    m_listEmitters.remove(_pEmitter);
}

/**
* 
* If the index/ID number passed in is within the range of the list, a pointer 
*	to the emitter at that position is returned. 
* If the ID passed in is not within the list range, zero is returned.
* 
* @author Rebeccah Cox
* @param uint32 _uiID - position/ID of the emitter to return.
* @return CParticleEmitter* - pointer to the emitter at the position passed in.
*/
CParticleEmitter*
CEmitterManager::GetEmitter(uint32 _uiID)
{
	// Set an iterator to the beginning of the list.
	std::list<CParticleEmitter*>::iterator iter = m_listEmitters.begin();

	// Increment the iterator until the index number passed in has been reached,
	// or the end of the list has been reached.
	for(uint32 uiIndex = 0; uiIndex < _uiID; ++uiIndex)
	{
		// If at the end of the list, return zero.
		if(iter == m_listEmitters.end())
		{
			return (0);
		}
		else
		{
			++iter;
		}
	}

	// Return a pointer to the emitter.
	return (*iter);
}

/*
* OnDeviceLost
* @author Rigardt de Vries
* @return void
*/
void
CEmitterManager::OnDeviceLost()
{
	for (std::list<CParticleEmitter*>::iterator iter = m_listEmitters.begin(); 
		iter != m_listEmitters.end(); ++iter)
    {
        (*iter)->OnDeviceLost();
    }
}

/*
* OnDeviceReset
* @author Rigardt de Vries
* @return void
*/
void
CEmitterManager::OnDeviceReset()
{
    for (std::list<CParticleEmitter*>::iterator iter = m_listEmitters.begin(); 
		iter != m_listEmitters.end(); ++iter)
    {
        (*iter)->OnDeviceReset();
    }
}

