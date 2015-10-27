// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateIdle.cpp
//  Description :   aistateIdle.cpp for implementation of aistateIdle.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../playermanager.h"
#include "../player.h"

// This Includes
#include "aistateIdle.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAIStateIdle::CAIStateIdle()
{

}

CAIStateIdle::~CAIStateIdle()
{

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
bool CAIStateIdle::Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
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

		return(true);
	}
	return(false);
}

void
CAIStateIdle::Process(float32 _fDeltaTick)
{
	//the AI is stalled, either after being disabled, or because it has just been spawned
	//decide which state to move into
	if(CAIPlayer::GetCanMove())
	{
		bool bGuard = m_pOwner->HasFlagGuard(m_eAllyTeam);
		if(m_pOwner->HasFlagGuard(m_eAllyTeam))
		{
			ReportStateChange(AI_STATE_GETFLAG);
		}
		else
		{
			ReportStateChange(AI_STATE_PROTECTFLAG);
		}
	}
	else
	{
		//check if the human players have moved outside of the starting area,
		// and if so, start moving.
		CPlayerManager& rPlayerManager = CPlayerManager::GetPlayerManagerInstance();
		CPlayer* pPlayer = 0;
		D3DXVECTOR2 vec2;
		for(uint32 i=0; i<8; ++i)
		{
			pPlayer = rPlayerManager.GetPlayer(i);
			if(pPlayer->IsHuman())
			{
				vec2 = pPlayer->GetTank()->GetPosition2D();
				if(TEAM_GREEN==pPlayer->GetTeam())
				{
					if((vec2.y >= 12)||(FACE_TOP!=pPlayer->GetTank()->GetFacePosition()))
					{
						CAIPlayer::SetCanMove(true);
					}
				}
				else
				{
					if((vec2.y <= 3)||(FACE_BOTTOM!=pPlayer->GetTank()->GetFacePosition()))
					{
						CAIPlayer::SetCanMove(true);
					}
				}
			}
		}
	}
}