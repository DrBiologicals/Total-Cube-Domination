// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flagparticleemitter.h
//  Description :   Declaration for CFlagParticleEmitter
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_FLAGPARTICLEEMITTER_H__
#define __IGFEB10_MODULE_FLAGPARTICLEEMITTER_H__

// Library Includes

// Local Includes
#include "particleemitter.h"

// Types

// Prototypes
class CFlag;


class CFlagParticleEmitter: public CParticleEmitter
{
	// Member Functions
public:
	CFlagParticleEmitter();
	virtual ~CFlagParticleEmitter();

	virtual bool Initialise(int32 _iNumParticles, const D3DXVECTOR3& _vec3Origin, CFlag* _pFlag);

	virtual void Resetparticle(TParticle* _pParticle);

	virtual void AddParticle();

	virtual void Process(float32 _fDeltaTick);

	virtual void PreDraw();
	virtual void Draw();
	virtual void PostDraw();

	virtual bool CheckAlive();

	virtual void OnDeviceLost();
    virtual void OnDeviceReset();

	static void SetTextureID(uint32 _uiID);

	void KillParticles();

protected:
	virtual void SetAlive(bool _bAlive);

	// Member Variables
public:

protected:
	CFlag* m_pFlag;

	EFacePosition m_eFace;

	float32 m_fSpawnTimer;

	static uint32 s_uiTextureID;

private:
}; 

#endif // __IGFEB10_MODULE_FLAGPARTICLEEMITTER_H__

