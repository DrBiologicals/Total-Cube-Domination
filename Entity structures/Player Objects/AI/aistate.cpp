// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistate.cpp
//  Description :   aistate.cpp for implementation of aistate.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "pathfinder.h"

// This Includes
#include "aistate.h"
#include "aisubstatemove.h"
#include "aisubstateattack.h"
#include "aisubstateflee.h"

// Static Variables
CCube* CAIState::s_pCube = 0;

// Static Function Prototypes


// Implementation

CAIState::CAIState()
{

}

CAIState::~CAIState()
{
	
}

bool CAIState::Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack)
{
	if(_pOwner!=0)
	{
		m_pOwner = _pOwner;
		m_pTank = m_pOwner->GetTank();
		m_pMove = _pMove;
		m_pFlee = _pFlee;
		m_pAttack = _pAttack;
		return(true);
	}
	return(false);
}

bool CAIState::InitGeneral()
{
	m_eAllyTeam = m_pTank->GetTeam();
	if(TEAM_GREEN==m_eAllyTeam)
	{
		m_eEnemyTeam = TEAM_PURPLE;
	}
	else
	{
		m_eEnemyTeam = TEAM_GREEN;
	}
	return true;
}

void
CAIState::Process(float32 _fDeltaTick)
{
	//do nothing
}

//requests for m_pOwner to change tha state
void
CAIState::ReportStateChange(EAIState _eNewState)
{
	m_pOwner->RequestState(_eNewState);
}

void CAIState::SetCube(CCube* _pCube)
{
	s_pCube = _pCube;
}