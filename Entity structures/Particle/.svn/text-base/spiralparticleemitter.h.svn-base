// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   spiralparticleemitter.h
//  Description :   Declaration for CSpiralParticleEmitter
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_SPIRALPARTICLEEMITTER_H__
#define __IGFEB10_MODULE_SPIRALPARTICLEEMITTER_H__

// Library Includes

// Local Includes
#include "particleEmitter.h"

// Types

// Prototypes
class CTank;

class CSpiralParticleEmitter : public CParticleEmitter
{
	// Member Functions
public:
    CSpiralParticleEmitter();
    virtual ~CSpiralParticleEmitter();

    virtual bool Initialise(int32 _iNumParticles, const D3DXVECTOR3& _vec3Origin, CTank* _pTank);

	virtual void Resetparticle(TParticle* _pParticle);

	virtual void AddParticle();

	virtual void Process(float32 _fDeltaTick);

	virtual void PreDraw();
	virtual void Draw();
	virtual void PostDraw();

	virtual bool IsEmpty();

    virtual bool IsAlive();

	virtual void OnDeviceLost();
    virtual void OnDeviceReset();

	static void SetTextureID(uint32 _uiID);

protected:
	virtual void RemoveDeadParticles();
	virtual void SetAlive(bool _bAlive);

private:

	// Member Variables
public:
    float32 m_fSpawnTimer;
    float32 m_fRotationAngle;

	static uint32 s_uiTextureID;

	EFacePosition m_eFace;
    CTank* m_pTank;

protected:

private:

}; 

#endif // __IGFEB10_MODULE_SPIRALPARTICLEEMITTER_H__

