// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   rules.h
//  Description :   Declaration for Crules
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_RULES_H__
#define __IGFEB10_MODULE_RULES_H__

// Library Includes

// Local Includes

// Types

// Prototypes
class CPlayer;
class CBullet;
class CMine;
class CEMPBomb;
class CFlagPlate;
class CHumanPlayer;
class CWall;
class CFlag;
class CTower;
class CFlameGrate;
class CBreakableBarrier;
class CPowerUp;
class CAmmo;

class CRules
{
	// Member Functions
public:

	CRules();
	~CRules();

	virtual bool Initialise();

	virtual int32 CheckWin();

	virtual void MineCollision(CTank* _pPlayerHit, CMine *_pMineFire) = 0;
	virtual void EMPCollision(CTank* _pPlayerHit, CEMPBomb *_pEMPFire) = 0;
	virtual void BulletTankCollision(CBullet* _pBullet, CTank* _pTankHit) = 0;
	virtual void BulletTowerCollision(CBullet* _pBullet, CTower* _pTowerHit) = 0;
	virtual void EMPTowerCollision(CEMPBomb* _pEMP, CTower* _pTower) = 0;

	void ChangeSide(CTank* _pTank, EFacePosition _eTargetFace);

	bool CaptureFlag(CTank* _pTank, CFlag* _pFlag);
	void GrabFlag(CTank* _pTank, CFlag* _pFlag);
	bool AwardPoint(ETeam _eTeam);

	int32 GetScore(ETeam _eTeam);
    void ResetScore();

	void SetFlagState(EFlagState _eFlagState, ETeam _eTeam);
	EFlagState GetFlagState(ETeam _eTeam);

#ifdef _DEBUG
	bool HasCheatMode(ECheatMode _eCheat);
#endif // _DEBUG
	void CheckCheatModeKeys(CPlayer* _pPlayer);

    void DestroyTank(CTank* _pTank);

	void FlameGrateCollision(CTank* _pTank, CFlameGrate* _pFlameGrate, float32 _fDeltaTick);
	void AmmoPlateCollision(CTank* _pTank, CAmmo* _pAmmoPlate);
	void BulletBarrierCollision(CBullet* _pBullet, CBreakableBarrier* _pBarrier);
	void BulletWallCollision(CBullet* _pBullet/*, CWall* _pWallHit*/);
	void EMPWallCollision(CEMPBomb* _pEMP);
	
	void PowerupCollision(CTank* _pTank, CPowerUp* _pPowerUp);

protected:

private:
	// Used by "CheckCheatModeKeys(...)".
#ifdef _DEBUG
	void SetCheatMode(ECheatMode _eCheat, bool _bIsActive);
#endif //_DEBUG
	// Member Variables
public:
	
protected:

private:
	int32 m_iTeamGreenScore;
	int32 m_iTeamPurpleScore;

	EFlagState m_eGreenFlagState;
	EFlagState m_ePurpleFlagState;

	// Cheat modes.
	bool m_abCheatModes[6];

}; 

#endif // __IGFEB10_MODULE_RULES_H__

