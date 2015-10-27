// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   bullet.h
//  Description :   Declaration for Cbullet
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BULLET_H__
#define __IGFEB10_MODULE_BULLET_H__

// Library Includes

// Local Includes
#include "projectile.h"

// Types
enum EOwnerType
{
	OWNER_TANK,
	OWNER_TOWER,
	OWNER_MAX
};

// Prototypes
class CTank;
class CTower;

class CBullet : public CProjectile
{
	// Member Functions
public:
	CBullet();
	virtual ~CBullet();

	static void LoadAssets();
	virtual bool Initialise(D3DXVECTOR3 _vec3Position, CTank* _pTankOwner, D3DXVECTOR3 _vec3Direction,
							D3DXVECTOR3 _vec3Right);
	bool Initialise(D3DXVECTOR3 _vec3Position, CTower* _pTowerOwner, D3DXVECTOR3 _vec3Direction,
							D3DXVECTOR3 _vec3Right);

	bool SetUpModel();
	
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	virtual float32 GetMoveSpeed();
	virtual void SetMoveSpeed(float32 _fmoveSpeed);

	virtual D3DXMATRIX& GetWorldMatrix();

	float32 GetDamage();
	void SetDamage(float32 _fDamage);

	void SetTankOwner(CTank* _pTankOwner);
	void SetTowerOwner(CTower* _pTowerOwner);
	CTank* GetTankOwner();
	CTower* GetTowerOwner();
	EOwnerType GetOwnerType();

    static void SetModelAndTextureID(uint32 _uiTextureID, uint32 _uiModelID, uint32 _uiGreenTextureID, uint32 _uiPurpleTextureID);

	virtual void StartTransition(EFacePosition _eTargetFace);

    virtual void SetAlive(bool _bAlive);

	const D3DXVECTOR3& GetDirection() const;
    const D3DXVECTOR3& GetRight() const;
    const D3DXVECTOR3& GetUp() const;

protected:

private:

	// Member Variables
public:

protected:
	CTank* m_pTankOwner;
	CTower* m_pTowerOwner;

	EOwnerType m_eOwnerType;

	ETeam m_eTeam;

    static uint32 s_uiTextureID;
	static uint32 s_uiGreenTextureID;
	static uint32 s_uiPurpleTextureID;
	static uint32 s_uiModelID;

	static uint32 s_uiSoundFireID1;
	static uint32 s_uiSoundFireID2;
	static uint32 s_uiSoundFireID3;

    float32 m_fCurrentTime;

private:

}; 

#endif // __IGFEB10_MODULE_BULLET_H__

