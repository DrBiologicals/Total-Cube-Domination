// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   tower.h
//  Description :   Declaration for Ctower
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TOWER_H__
#define __IGFEB10_MODULE_TOWER_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <list>

// Local Includes
#include "../../../defines.h"
#include "../../entity.h"
#include "../tile.h"
#include "../../../angle.h"

// Types

// Prototypes
class CTowerAIState;
class CBullet;

class CTower : public CTile
{
	// Member Functions
public:
	CTower();
	virtual ~CTower();

	bool Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, ETeam _eTeam, uint32 _uiTextureID, uint32 _uiDisabledTextureID,
		uint32 _uiModelID, uint32 _uiTurretModelID);
	virtual void Process(float32 _fDeltaTick);
	void Draw();

	bool SetTurretModel(int32 _iModelID);

	bool SetAIState(ETowerAIState _nextState);

	float32 TakeDamage(float32 _fDamage);
	void TakeEMP();

	void SetCurrentShield(float32 _fShield);
	const float32 GetCurrentShield();
	const float32 GetMaxShield();

	ETowerAIState GetCurrentAIStateEnum();
	CTowerAIState* GetCurrentAIState();

	std::list<CBullet*>& GetBulletList();

	ETeam GetTeam();

	void RotateTurret(float32 _fRadian, float32 _fDeltaTick);
	void Shoot();
	const D3DXVECTOR3& GetPosition() const;

protected:

private:

	// Member Variables
public:

protected:
	ETeam m_eTeam;

	ETowerAIState m_eCurrentState;
	ETowerAIState m_eNextState;
	CTowerAIState* m_pCurrentState;

	uint32 m_uiTurretModelID;
	uint32 m_uiDisabledTextureID;

	std::list<CBullet*> m_listBullets;

	CTowerAIState* m_pTowerAI;
	float32 m_fMaxShieldStrength;
	float32 m_fShieldStrength;
	float32 m_fCooldownLength;
	float32 m_fPlasmaCoolDown;

	D3DXMATRIX m_matTurretWorld;
	D3DXVECTOR3 m_vec3TurretNorm;
	D3DXVECTOR3 m_vec3ShootDir;
	D3DXVECTOR3 m_vec3ShootRight;

	CAngle m_turretAngle;
	float32 m_fTurnSpeed;

private:

}; 

#endif // __IGFEB10_MODULE_TOWER_H__

