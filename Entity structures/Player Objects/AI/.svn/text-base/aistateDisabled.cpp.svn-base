// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateDisabled.cpp
//  Description :   aistateDisabled.cpp for implementation of aistateDisabled.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Includes
#include "aistateDisabled.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAIStateDisabled::CAIStateDisabled()
{

}

CAIStateDisabled::~CAIStateDisabled()
{

}

void
CAIStateDisabled::Process(float32 _fDeltaTick)
{
	//unit is disabled, probably through an EMP
	if((!m_pTank->GetDisabled())&&(m_pTank->GetAlive()))
	{
		m_pOwner->RequestState(AI_STATE_IDLE);
	}

	//keep checking to see if the tank is no longer disabled, and if so,
	// set to Idle
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
bool CAIStateDisabled::Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack)
{
	if(_pOwner!=0)
	{
		m_pOwner = _pOwner;
		m_pTank = m_pOwner->GetTank();

		/*InitGeneral();

		if(TEAM_GREEN==m_eAllyTeam)
		{
			
		}
		if(TEAM_PURPLE==m_eAllyTeam)
		{
			
		}*/
		return(true);
	}
	return(false);
}