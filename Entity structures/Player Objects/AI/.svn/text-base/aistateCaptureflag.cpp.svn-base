// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateCaptureflag.cpp
//  Description :   aistateCaptureflag.cpp for implementation of aistateCaptureflag.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../terrain objects/flagplate.h"
#include "../../terrain objects/flag.h"

// This Includes
#include "aistateCaptureflag.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAIStateCaptureFlag::CAIStateCaptureFlag()
{
	
}

CAIStateCaptureFlag::~CAIStateCaptureFlag()
{
	
}

void
CAIStateCaptureFlag::Process(float32 _fDeltaTick)
{
	m_pMove->Process(_fDeltaTick);

	//unit currently has the flag and main goal is to return to base
	//projectiles are disabled, mines enabled, speed is hindered

	//if no enemy is around, move to the team's base
	//if being chased, flee towards the base (if possible) and drop mine where enemy might travel over

	//IDEAL - shouldn't follow a predictable path
	//		- shouldn't remain on ally flag tile
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
bool CAIStateCaptureFlag::Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
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

		//CFlag* pAllyFlag = s_pCube->GetFlag(m_eAllyTeam);
		//pAllyFlag->

		CFlagPlate* pFlagPlate = s_pCube->GetFlagPlate(m_eAllyTeam);
		m_pMove->SetTarget(pFlagPlate->GetX(),pFlagPlate->GetY(),pFlagPlate->GetFacePosition());
		return(true);
	}
	return(false);
}