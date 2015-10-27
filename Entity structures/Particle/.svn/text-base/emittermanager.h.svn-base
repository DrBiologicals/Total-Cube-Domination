// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   emittermanager.h
//  Description :   Declaration for Cemittermanager
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_EMITTERMANAGER_H__
#define __IGFEB10_MODULE_EMITTERMANAGER_H__

// Library Includes
#include <list>

// Local Includes
#include "../entity.h"

// Types

// Prototypes
class CParticleEmitter;
class CFlameGrate;
class CFlag;
class CTank;
class CBullet;

class CEmitterManager : public CEntity
{
	// Member Functions
public:
	bool Initialise();

	static CEmitterManager& GetInstance();
	static void DestroyInstance();

	virtual void Process(float32 _fDeltaTick);

	uint32 AddEmitter(int32 _iNumParticles, D3DXVECTOR3 _vec3Origin, EParticleType _eType, ETeam _eTeam,
                        CFlameGrate* _pFlameGrate = 0, CFlag* _pFlag = 0, CTank* _pTank = 0, CBullet* _pBullet = 0);
    void RemoveEmitter(CParticleEmitter* _pEmitter);

    void OnDeviceLost();
    void OnDeviceReset();

	CParticleEmitter* GetEmitter(uint32 _uiID);

    void Clear();

protected:
	CEmitterManager();
	virtual ~CEmitterManager();

private:

	// Member Variables
public:

protected:
	std::list<CParticleEmitter*> m_listEmitters;
	static CEmitterManager* s_pInstance;

private:

}; 

#endif // __IGFEB10_MODULE_EMITTERMANAGER_H__

