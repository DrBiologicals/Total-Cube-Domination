// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateProtectplayer.cpp
//  Description :   aistateProtectplayer.cpp for implementation of aistateProtectplayer.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Includes
#include "aistateProtectplayer.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAIStateProtectPlayer::CAIStateProtectPlayer()
: m_pFlagCarrier(0)
{
	m_TTargetLastPos2.x = -1;
	m_TTargetLastPos2.y = -1;
}

CAIStateProtectPlayer::~CAIStateProtectPlayer()
{
	m_pFlagCarrier = 0;
}

/*
* Initialises the class instance
*
* @author				Cameron MacIntosh
* @param _pOwner		the owning AIPlayer
* @param _pMove			an address of an instance of the Move substate
* @param _pFlee			an address of an instance of the Flee substate
* @param Attack			an address of an instance of the Attack substate
* @return				if it succeded. Don't use the instance if it returns false.
*/
bool CAIStateProtectPlayer::Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack)
{
	if(_pOwner!=0)
	{
		m_pOwner = _pOwner;
		m_pTank = m_pOwner->GetTank();

		m_pMove = _pMove;
		m_pFlee = _pFlee;
		m_pAttack = _pAttack;

		InitGeneral();

		for(uint32 i=0; i<8; ++i)
		{
			CTank* pTank = CPlayerManager::GetPlayerManagerInstance().GetPlayer(i)->GetTank();
			if((m_eEnemyTeam!=pTank->GetTeam())&&(pTank!=m_pTank))
			{
				if(pTank->HasFlag())
				{
					//carrier has flag
					m_pFlagCarrier = pTank;
					D3DXVECTOR2 vec2 = pTank->GetPosition2D();
					m_TTargetLastPos2.x = static_cast<int32>(vec2.x);
					m_TTargetLastPos2.y = static_cast<int32>(vec2.y);
					m_pMove->SetTarget(m_TTargetLastPos2.x, m_TTargetLastPos2.y, pTank->GetFacePosition());
				}
			}
		}
		if(m_pFlagCarrier==0)
		{
			m_pOwner->RequestState(AI_STATE_IDLE);
			return(false);
		}
		return(true);
	}
	return(false);
}

void
CAIStateProtectPlayer::Process(float32 _fDeltaTick)
{
	//Protect an Ally player (probably carrying the flag, and if so, can't use projectiles, may be slower)
	//shouldn't block the protected ally's path
	//will more likely to attack, less likely to flee

	int32 iTankX = static_cast<int32>(m_pTank->GetPosition2D().x);
	int32 iTankY = static_cast<int32>(m_pTank->GetPosition2D().y);
	D3DXVECTOR2 vec2;

	if(m_pFlagCarrier==0)
	{
		m_pOwner->RequestState(AI_STATE_IDLE);
		return;
	}
	if(m_pFlagCarrier->GetAlive())
	{
		//if the target has moved
		vec2 = m_pFlagCarrier->GetPosition2D();
		TIPoint tTargetPoint;
		tTargetPoint.x = static_cast<int32>(vec2.x);
		tTargetPoint.y = static_cast<int32>(vec2.y);
		if((m_TTargetLastPos2.x!=tTargetPoint.x)||(m_TTargetLastPos2.y!=tTargetPoint.y))
		{
			//calculate the new path if its allowed.
			if(m_pOwner->GetAIID()==m_pOwner->GetLastCalcID())
			{
				m_pMove->SetTarget(tTargetPoint.x, tTargetPoint.y, m_pFlagCarrier->GetFacePosition());
				m_TTargetLastPos2 = tTargetPoint;
				m_pMove->Process(_fDeltaTick);
			}
		}
		else
		{
			m_pMove->Process(_fDeltaTick);
		}
	}
	else //flag carrier is dead
	{
		//flag would drop to the floor, set state to getFlag
		m_pOwner->RequestState(AI_STATE_GETFLAG);
	}
	//if protected ally dies:
	//	- if flag is close, most likely switch to GetFlag
	//	- if close ally is weak, most likely attempt to kill (this might occur in GetFlag)
	//	- probably always switch to GetFlag

	//IDEAL - will work together with an ally in the Capture Flag state, which would result in
	//			the ally moving out of the way, giving the protecting AI a clear path to rush
	//			incoming enemies, and block of their path.
	//		- AI should simulate a human, so best cases shouldn't always occur.
}