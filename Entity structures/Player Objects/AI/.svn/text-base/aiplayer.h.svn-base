// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aiplayer.h
//  Description :   Declaration for CAIPlayer
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AIPLAYER_H__
#define __IGFEB10_MODULE_AIPLAYER_H__

#ifdef _DEBUG
	#define _AI_NOSHOOT
#endif //_DEBUG

// Library Includes
#include <vector>
// Local Includes
#include "../player.h"
#include "../../../defines.h"
#include "aistate.h"
#include "aihelper.h"

// Types

// Prototypes
class CAIState;
class CAISubstate;
class CAISubstateMove;
class CAISubstateFlee;
class CAISubstateAttack;
enum EAIState;
class CPathfinder;
class CCube;

class CAIPlayer : public CPlayer
{
	// Member Functions
public:
	CAIPlayer();
	virtual ~CAIPlayer();
	virtual bool Initialise(CTank* _pTank, int32 _iIDNumber, ETeam _eTeam);
	virtual void Process(float32 _fDeltaTick);
	
	virtual void RequestState(EAIState _eNextState);

	

	// Getter functions.
	int32 CAIPlayer::GetAIID();
	int32 GetAITotal();
	CAIPlayer* GetAIPlayer(uint32 _uiID);
	EAIState GetCurrentStateEnum();
	CAIState* GetCurrentState();

	static void SetCube(CCube* _pCube);
	static int32 GetLastCalcID();
	static bool HasFlagGuard(ETeam _eTeam);
	static void SetFlagGuard(ETeam _eTeam, bool _bIsGuard);
	static bool GetCanMove();
	static void SetCanMove(bool _bCanMove);

protected:

private:
	virtual bool ChangeState();
	// Member Variables
public:
	
protected:
	CAIState* m_pCurrentState;
	EAIState m_eCurrentState;
	EAIState m_eNextState;
	bool m_bInitialised;

	CAISubstateMove* m_pMove;
	CAISubstateFlee* m_pFlee;
	CAISubstateAttack* m_pAttack;

	uint32 m_uiID;

	D3DXVECTOR2 m_vec2lastPos;
	//STATIC
	static uint32 s_uiAITotal;
	static std::vector<CAIPlayer*> s_vAIPlayers;
	static float32 s_fTime;
	static CAIPlayer* s_pOriginPlayer;
	static uint32 s_uiLastCalc;
	static float32 s_fCalcDist;
	static bool s_bGreenGuard;
	static bool s_bPurpleGuard;

	static bool s_bCanMove;
private:

}; 

#endif // __IGFEB10_MODULE_AIPLAYER_H__

