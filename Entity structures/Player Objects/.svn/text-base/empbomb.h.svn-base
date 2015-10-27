// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   empbomb.h
//  Description :   Declaration for Cempbomb
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_EMPBOMB_H__
#define __IGFEB10_MODULE_EMPBOMB_H__

// Library Includes

// Local Includes
#include "projectile.h"

// Types

// Prototypes
class CTank;

class CEMPBomb : public CProjectile
{
	// Member Functions
public:
	CEMPBomb();
	~CEMPBomb();

	static void LoadAssets();
	virtual bool Initialise(D3DXVECTOR3 _vec3Position, CTank* _pTankOwner, D3DXVECTOR3 _vec3Direction, D3DXVECTOR3 _vec3Right);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	virtual float32 GetDamage();
	virtual void SetDamage(float32 _fDamage);

	virtual float32 GetMoveSpeed();
	virtual void SetMoveSpeed(float32 _fmoveSpeed);

	virtual D3DXMATRIX& GetWorldMatrix();

	virtual void SetBlastRadius(float32 _fRadius);
	virtual float32 GetBlastRadius();

	virtual float32 GetMaxDistance();

	float32 GetCurrentDistance();
	void SetCurrentDistance(float32 _fDistance);

	virtual void SetOwner(CTank* _pTankOwner);
	virtual CTank* GetOwner();

	static void SetAssetIDs(uint32 _uiModelID, uint32 _uiTextureID, uint32 _uiSoundID);
	static void SetExpldAssestIDs(uint32 _uiModelID, uint32 _uiTextureID, uint32 _uiSoundID);

	void Detonate();

	virtual void StartTransition(EFacePosition _eTargetFace);

    CTank* GetTank(int32 _iTankID);
    bool AddTankHit(CTank* _pTank);

protected:

private:

	// Member Variables
public:

protected:
	CTank* m_pTankOwner;
    CTank* m_aTanksHit[8];

	float32 m_fExplodeTimer;
	float32 m_fBlastRadius;
	float32 m_fMaxBlastRadius;
	float32 m_fMaxDistance;
	float32 m_fCurrentDistance;

	D3DXVECTOR3 m_vec3Origin;

	bool m_bDetonating;

	static uint32 s_uiTextureID;
	static uint32 s_uiModelID;
	static uint32 s_uiExpldTextureID;
	static uint32 s_uiExpldModelID;

	static uint32 s_uiSoundID;
	static uint32 s_uiExpldSoundID;
	static uint32 s_uiEmptySoundID;

private:

}; 

#endif // __IGFEB10_MODULE_EMPBOMB_H__

