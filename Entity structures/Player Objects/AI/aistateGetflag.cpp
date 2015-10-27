// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateGetflag.cpp
//  Description :   aistateGetflag.cpp for implementation of aistateGetflag.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../terrain objects/cube.h"
#include "../../terrain objects/flagplate.h"
#include "../../terrain objects/flag.h"

// This Includes
#include "aistateGetflag.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAIStateGetFlag::CAIStateGetFlag()
{
	
}

CAIStateGetFlag::~CAIStateGetFlag()
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
bool CAIStateGetFlag::Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
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

		m_pAllyFlag = s_pCube->GetFlag(m_eAllyTeam);
		m_pEnemyFlag = s_pCube->GetFlag(m_eEnemyTeam);
		
		//set the path to the flag (regardless of position)
		D3DXVECTOR2 _vec2Target(0,0);
		mFlagPos3Last = m_pEnemyFlag->GetPosition();

		CPathfinder::ConvertUnit3DtoTile2D(m_pEnemyFlag->GetFace(), mFlagPos3Last, _vec2Target);
		m_pMove->SetTarget(static_cast<int16>(_vec2Target.x),static_cast<int16>(_vec2Target.y),m_pEnemyFlag->GetFace());

		return(true);
	}
	return(false);
}

void
CAIStateGetFlag::Process(float32 _fDeltaTick)
{
	//m_pMove->Process(_fDeltaTick);
	//if the enemy team's flag is still on it's plate
	if(m_pEnemyFlag->IsFlagOnFlagPlate())
	{
		m_pMove->Process(_fDeltaTick);
	}
	else
	{
		//does an ally have the flag(?)
		if(m_pEnemyFlag->GetFlagPickedUp())
		{
			if(m_pTank->HasFlag())
			{
				m_pOwner->RequestState(AI_STATE_CAPTUREFLAG);
			}
			else
			{
				m_pOwner->RequestState(AI_STATE_PROTECTPLAYER);
			}
		}
		//if no ally has the flag
		else
		{
			//check to see if the flag position is different than stored in the pathfinder
			//move towards it
			if(mFlagPos3Last!=m_pEnemyFlag->GetPosition())
			{
				mFlagPos3Last = m_pEnemyFlag->GetPosition();
				D3DXVECTOR2 _vec2Target(0,0);
				CPathfinder::ConvertUnit3DtoTile2D(m_pEnemyFlag->GetFace(), mFlagPos3Last, _vec2Target);
				m_pMove->SetTarget(static_cast<int16>(_vec2Target.x),static_cast<int16>(_vec2Target.y),m_pEnemyFlag->GetFace());
			}
			m_pMove->Process(_fDeltaTick);
		}
	}

}