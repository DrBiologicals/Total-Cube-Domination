// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   gamestate.h
//  Description :   Declaration for CGameState
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_GAMESTATE_H__
#define __IGFEB10_MODULE_GAMESTATE_H__

// Library Includes
#include <vector>
#include <list>

// Local Includes
#include "programstate.h"

// Types

// Prototypes
class CCube;
class CTank;
class CPlayer;
class CRules;
class CProjectile;
class CDebugWindow;
class CBullet;
class CStatistics;
class CPauseScreen;

class CGameState : public CProgramState
{
	// Member Functions
public:
	CGameState();
	virtual ~CGameState();

	virtual void Process(float32 _fDeltaTick);
	virtual bool Initialise();

	bool LoadLevel(const char* _kpcFileName);

	void NewRound();
    void NewGame();

	bool IsNewRound();

	CRules* GetRules();
	CDebugWindow* GetDebugWindow();

    void TankCollisions(float32 _fDeltaTick);
    void ChangeFaceCollisions(int32 _iTankID, uint32 _uiEdgeID);
    void TankBulletCollisions(int32 _iTankID, std::list<CBullet*> _pListBullets);
	void TankBulletChangeFaceCollisions(CProjectile* _pProjectile);
    void TankPlateCollisions(int32 _iTankID, float32 _fDeltaTick);
    void TowerBulletCollisions();
    void FlagCollisions();
	void TankMineCollisions();
	void TankEMPCollisions();
	void TankPowerupCollision();
	void FlagTowerShutdown();

	bool GetPause();
	void SetPause(bool _bPaused);

protected:

private:

	// Member Variables
public:

protected:
	CCube* m_pCube;
	CTank* m_apTanks[8];
	CPlayer* m_apPlayer[8];
    CRules* m_pRules;
	CStatistics* m_apStats[4];
	CDebugWindow* m_pDebugWindow;
	CPauseScreen* m_pPauseScreen;

    float32 m_fNewGameTimer;
	float32 m_fPauseTimer;
	float32 m_fNewRoundTimer;
	bool m_bPause;
	bool m_bPauseDown;
	bool m_bNewRound;

	uint32 m_uiMusic;

private:

}; 

#endif // __IGFEB10_MODULE_GAMESTATE_H__

