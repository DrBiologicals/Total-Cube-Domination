// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   bullettrailparticleemitter.h
//  Description :   Declaration for CBulletTrailParticleEmitter
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BULLETTRAILPARTICLEEMITTER_H__
#define __IGFEB10_MODULE_BULLETTRAILPARTICLEEMITTER_H__

// Library Includes

// Local Includes
#include "particleemitter.h"

// Types

// Prototypes
class CBullet;
class CTank;

class CBulletTrailParticleEmitter : public CParticleEmitter
{
	// Member Functions
public:
    CBulletTrailParticleEmitter();
    virtual ~CBulletTrailParticleEmitter();

    virtual bool Initialise(int32 _iNumParticles, const D3DXVECTOR3& _vec3Origin, CBullet* _pBullet, ETeam _eTeam);

    virtual void Resetparticle(TParticle* _pParticle);

	virtual void AddParticle();

	virtual void Process(float _fDeltaTick);

	virtual void PreDraw();
	virtual void Draw();
	virtual void PostDraw();

    void SetOrigin(D3DXVECTOR3& _vec3Origin);

	virtual bool IsEmpty();

	virtual bool CheckAlive();

	virtual bool IsAlive();

    static void SetTextureID(uint32 _uiID);

    virtual void SetAlive(bool _bAlive);

    void SetBullet(CBullet* _pBullet);

    bool CheckBullet();

protected:
	virtual void RemoveDeadParticles();

private:

	// Member Variables
public:

protected:
    CBullet* m_pBullet;
    CTank* m_pTankOwner;

    // emit variables
    float32 m_fEmitRate;
    float32 m_fEmitTimer;

    ETeam m_eTeam;

    static uint32 s_uiTextureID;

private:

}; 

#endif // __IGFEB10_MODULE_BULLETTRAILPARTICLEEMITTER_H__

