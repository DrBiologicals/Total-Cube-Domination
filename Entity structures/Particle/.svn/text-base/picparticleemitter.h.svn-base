// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   cpicparticleemitter.h
//  Description :   Declaration for CCPICParticleEmitter
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PICPARTICLEEMITTER_H__
#define __IGFEB10_MODULE_PICPARTICLEEMITTER_H__

// Library Includes

// Local Includes
#include "particleEmitter.h"

// Types

// Prototypes
class CTank;

class CPICParticleEmitter : public CParticleEmitter
{
	// Member Functions
public:
	CPICParticleEmitter();
	virtual ~CPICParticleEmitter();

	virtual bool Initialise(int32 _iNumParticles, const D3DXVECTOR3& _vec3Origin, CTank* _pTank);

	virtual void Resetparticle(TParticle* _pParticle);

	virtual void AddParticle();

	virtual void Process(float32 _fDeltaTick);

	virtual void PreDraw();
	virtual void Draw();
	virtual void PostDraw();

	virtual bool IsEmpty();

	virtual bool IsAlive();

	virtual bool CheckAlive();

	virtual void OnDeviceLost();
    virtual void OnDeviceReset();

	void SetPicType(EPIC _ePicType);

	static void LoadAssets();
	static void ResetAssets();

protected:
	virtual void SetAlive(bool _bAlive);

private:

	// Member Variables
public:

protected:
	CTank* m_pTank;

	EPIC m_ePICType;

	static uint32 s_uiMoveID;
	static uint32 s_uiBulletMoveID;
	static uint32 s_uiBulletDamageID;
	static uint32 s_uiShieldID;
	static uint32 s_uiRadiusID;

private:

}; 

#endif // __IGFEB10_MODULE_PICPARTICLEEMITTER_H__

