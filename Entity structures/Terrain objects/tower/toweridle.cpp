// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   toweridle.cpp
//  Description :   toweridle.cpp for implementation of toweridle.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../player objects/tank.h"
#include "../../player objects/playermanager.h"
#include "../../player objects/player.h"

// This Includes
#include "toweridle.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
*
* Constructor for CTowerIdle
*
* @author				Cameron MacIntosh
*
*/
CTowerIdle::CTowerIdle()
{

}

/**
* Deconstructor for CTowerIdle
*
* @author				Cameron MacIntosh
*
*/
CTowerIdle::~CTowerIdle()
{

}

/**
*
* sets the starting values for the instance
*
* @author				Cameron MacIntosh
* @param _pOwnerTower	The tower that owns the AI
*
*/
bool
CTowerIdle::Initialise(CTower *_pOwnerTower)
{
	if(_pOwnerTower!=0)
	{
		m_pTower = _pOwnerTower;
		return (true);
	}
	return false;
}

/**
* Processes the state
*   changes the tower's state to attack if enemy is close
*
* @author				Cameron MacIntosh
* @param _fDeltaTick	Time between frames
*/
void
CTowerIdle::Process(float32 _fDeltaTick)
{
	// check through all tanks that are on the same face as this player.
	for (uint32 ui = 0; ui < 8; ++ui)
	{
		CTank* pTank = CPlayerManager::GetPlayerManagerInstance().GetPlayer(ui)->GetTank();

		if ((pTank->GetFacePosition() == m_pTower->GetFacePosition()) && (pTank->GetTeam() != m_pTower->GetTeam()) )
		{
			m_pTower->SetAIState(TOWERAI_STATE_ATTACK);
		}
	}

	//if an enemy moves close, switch to Attack
	m_pTower->SetAIState(TOWERAI_STATE_ATTACK);
}