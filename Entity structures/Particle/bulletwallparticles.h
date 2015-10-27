// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   bulletwallparticles.h
//  Description :   Declaration for CBulletWallParticles
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BULLETWALLPARTICLES_H__
#define __IGFEB10_MODULE_BULLETWALLPARTICLES_H__

// Library Includes

// Local Includes
#include "particleemitter.h"
// Types

// Prototypes
class CBullet;

class CBulletWallParticles : public CParticleEmitter
{
public:
	CBulletWallParticles();
	virtual ~CBulletWallParticles();

	virtual bool Initialise(int32 _iNumParticles, const D3DXVECTOR3& _vec3Origin, EParticleType _eType, CBullet* _pBullet);

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
	virtual void SetAlive(bool _bAlive);

private:

	// Member Variables
public:

protected:
	static uint32 s_uiTextureID;
	CBullet* m_pBullet;

private:

}; 

#endif // __IGFEB10_MODULE_BULLETWALLPARTICLES_H__

