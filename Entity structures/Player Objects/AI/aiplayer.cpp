// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aiplayer.cpp
//  Description :   aiplayer.cpp for implementation of aiplayer.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "aistate.h"
#include "aistateCaptureflag.h"
#include "aistateDisabled.h"
#include "aistateGetflag.h"
#include "aistateIdle.h"
#include "aisubstateMove.h"
#include "aisubstateFlee.h"
#include "aisubstateAttack.h"
#include "aistateProtectflag.h"
#include "aistateProtectplayer.h"
#include "aistateRetrieveflag.h"
#include "pathfinder.h"
#include "../playermanager.h"
#include "../humanplayer.h"
#include "../tank.h"
#include "../../terrain objects/wall.h"

#include "../../../engine/game/gamestate.h"
#include "../../../engine/game/rules.h"
#include "../../../engine/TotalCubeDomination.h"

// This Includes
#include "aiplayer.h"

// Static Variables
uint32 CAIPlayer::s_uiAITotal = 0;
float32 CAIPlayer::s_fTime = 0.0f;
CAIPlayer* CAIPlayer::s_pOriginPlayer = 0;
uint32 CAIPlayer::s_uiLastCalc = 0;
float32 CAIPlayer::s_fCalcDist = 0.f;
std::vector<CAIPlayer*> CAIPlayer::s_vAIPlayers;
bool CAIPlayer::s_bGreenGuard = false;
bool CAIPlayer::s_bPurpleGuard = false;
bool CAIPlayer::s_bCanMove = false;
// Static Function Prototypes

// Implementation

CAIPlayer::CAIPlayer()
: m_pCurrentState(0)
, m_eCurrentState(AI_STATE_NULL)
, m_pMove(0)
, m_pFlee(0)
, m_pAttack(0)
, m_bInitialised(false)
, m_uiID(0)
{
	s_vAIPlayers.push_back(this);
}

CAIPlayer::~CAIPlayer()
{
	--s_uiAITotal;
	delete m_pCurrentState; m_pCurrentState = 0;
	if(m_pMove!=0){ delete m_pMove; m_pMove = 0;		}
	if(m_pFlee!=0){ delete m_pFlee; m_pFlee = 0;		}
	if(m_pAttack!=0){ delete m_pAttack; m_pAttack = 0;	}
}

/*
* Initialises the instance
* @author						Cameron MacIntosh
* @param _pTank					a pointer to the tank
* @param _iIDNumber				the id of the tank
* @param _eTeam					the player's team
* @param _tPlayerSpawnLocation	the spawn location of the tank
* @return bool					if the function succeeded
*/
bool
CAIPlayer::Initialise(CTank* _pTank,int32 _iIDNumber, ETeam _eTeam)
{
	m_pTank = _pTank;
	m_iPlayerID = _iIDNumber;
	m_eTeam = _eTeam;

	m_vec2lastPos = m_pTank->GetPosition2D();

	//create the substates
	m_pMove = new CAISubstateMove();
	m_pMove->Initialise(m_pTank);
	m_pFlee = new CAISubstateFlee();
	m_pFlee->Initialise(m_pTank);
	m_pAttack = new CAISubstateAttack();
	m_pAttack->Initialise(m_pTank);

	//set the state to idle
	m_eNextState = AI_STATE_IDLE;
	ChangeState();

	m_bInitialised = true;

	if(s_uiAITotal==0)
	{
		s_pOriginPlayer = this;
	}
	m_uiID = s_uiAITotal;
	++s_uiAITotal;

	m_bIsHuman = false;

	return (true);
}

/*
* Processes the instance
* @author				Cameron MacIntosh
* @param _fDeltaTick	The time that has passed since the last frame
*/
void
CAIPlayer::Process(float32 _fDeltaTick)
{
	CPlayer::Process(_fDeltaTick);

	if(_fDeltaTick>0.0f)
	{
		if(this==s_pOriginPlayer)
		{
			s_fTime += _fDeltaTick;
			if(s_fTime>s_fCalcDist)
			{
				s_fTime -= s_fCalcDist;
				s_uiLastCalc ++;
				if(s_uiLastCalc>=s_uiAITotal)
				{
					s_uiLastCalc = 0;
				}
			}
		}

		if(m_bInitialised&&(!m_pTank->IsTransitioning()))
		{
			if((m_pTank->GetDisabled())||(!m_pTank->GetAlive()))
			{
				RequestState(AI_STATE_DISABLED);
			}
			//changes state if a change has been requested
			ChangeState();
			if(ChangeState())
			{
				//state has changed
			}
			else
			{
				//state has not changed
			}
			m_pCurrentState->Process(_fDeltaTick);
		}
	}

}

/*
* request a state change (changes on next Process() call
* @author				Cameron MacIntosh
* @param _eNextState	the state that is now desired
*/
void
CAIPlayer::RequestState(EAIState _eNextState)
{
	m_eNextState = _eNextState;
	if(m_eNextState==AI_STATE_PROTECTFLAG)
	{
		SetFlagGuard(GetTeam(), true);
	}
}

int32 CAIPlayer::GetAIID()
{
	return (m_uiID);
}

int32 CAIPlayer::GetAITotal()
{
	return(s_uiAITotal);
}

CAIPlayer* CAIPlayer::GetAIPlayer(uint32 _uiID)
{
	if(_uiID<s_uiAITotal)
	{
		return(s_vAIPlayers[_uiID]);
	}
	return 0;
}

/*
* returns the enum of the current AIState
* @author				Cameron MacIntosh
* @return EAIState		the e
num of the current state
*/
EAIState
CAIPlayer::GetCurrentStateEnum()
{
	return (m_eCurrentState);
}

CAIState*
CAIPlayer::GetCurrentState()
{
	return (m_pCurrentState);
}

/// change the state (private function, called through Process() )
bool
CAIPlayer::ChangeState()
{
	if(m_eNextState != m_eCurrentState)
	{
		if(0!=m_pCurrentState)
		{
			delete m_pCurrentState;
			m_pCurrentState = 0;
		}
		switch (m_eNextState)
		{
		case AI_STATE_IDLE:
			m_pCurrentState = new CAIStateIdle();
			break;
		case AI_STATE_GETFLAG:
			m_pCurrentState = new CAIStateGetFlag();
			break;
		case AI_STATE_CAPTUREFLAG:
			m_pCurrentState = new CAIStateCaptureFlag();
			break;
		case AI_STATE_DISABLED:
			m_pCurrentState = new CAIStateDisabled();
			break;
		case AI_STATE_PROTECTFLAG:
			m_pCurrentState = new CAIStateProtectFlag();
			break;
		case AI_STATE_PROTECTPLAYER:
			m_pCurrentState = new CAIStateProtectPlayer();
			break;
		case AI_STATE_RETRIEVEFLAG:
			m_pCurrentState = new CAIStateRetrieveFlag();
			break;
		}
		m_pCurrentState->Initialise(this, m_pMove, m_pFlee, m_pAttack);
		m_eCurrentState = m_eNextState;
		return (true);
	}
	
	return (false);
}

void CAIPlayer::SetCube(CCube* _pCube)
{
	CAIState::SetCube(_pCube);
	CAISubstate::SetCube(_pCube);
}

/*
* 
*/
int32 CAIPlayer::GetLastCalcID()
{
	return(s_uiLastCalc);
}

bool CAIPlayer::HasFlagGuard(ETeam _eTeam)
{
	if(TEAM_GREEN==_eTeam)
	{
		return(s_bGreenGuard);
	}
	if(TEAM_PURPLE==_eTeam)
	{
		return(s_bPurpleGuard);
	}
	return false;
}

void CAIPlayer::SetFlagGuard(ETeam _eTeam, bool _bIsGuard)
{
	if(TEAM_GREEN==_eTeam)
	{
		s_bGreenGuard = _bIsGuard;
	}
	if(TEAM_PURPLE==_eTeam)
	{
		s_bPurpleGuard = _bIsGuard;
	}
}

//returns if the AI player can move. Used in forcing AI to wait until humans are ready to begin
bool CAIPlayer::GetCanMove()
{
	return(s_bCanMove);
}

void CAIPlayer::SetCanMove(bool _bCanMove)
{
	s_bCanMove = _bCanMove;
}