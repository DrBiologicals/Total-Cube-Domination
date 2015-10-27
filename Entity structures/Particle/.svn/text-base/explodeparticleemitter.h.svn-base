// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   explodeparticleemitter.h
//  Description :   Declaration for CExplodeParticleEmitter
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_EXPLODEPARTICLEEMITTER_H__
#define __IGFEB10_MODULE_EXPLODEPARTICLEEMITTER_H__

// Library Includes

// Local Includes
#include "particleemitter.h"

// Types

// Prototypes
class CExplodeParticleEmitter : public CParticleEmitter
{
	// Member Functions
public:
	CExplodeParticleEmitter();
	virtual ~CExplodeParticleEmitter();

	virtual bool Initialise(int32 _iNumParticles, const D3DXVECTOR3& _vec3Origin, ETeam _eTeam);

	virtual void Resetparticle(TParticle* _pParticle);

	virtual void AddParticle();

	virtual void Process(float32 _fDeltaTick);

	virtual void PreDraw();
	virtual void Draw();
	virtual void PostDraw();

	virtual bool IsEmpty();

	virtual bool CheckAlive();

	virtual void OnDeviceLost();
    virtual void OnDeviceReset();

	static void SetTextureID(uint32 _uiID);

protected:
	virtual void RemoveDeadParticles();
	virtual void SetAlive(bool _bAlive);

private:

	// Member Variables
public:

protected:
	static uint32 s_uiTextureID;

	ETeam m_eTeam;

private:

}; 

#endif // __IGFEB10_MODULE_EXPLODEPARTICLEEMITTER_H__

