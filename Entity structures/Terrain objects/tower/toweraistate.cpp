// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   toweraistate.cpp
//  Description :   toweraistate.cpp for implementation of toweraistate.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "tower.h"
#include "toweridle.h"
#include "../../../defines.h"
// This Includes
#include "toweraistate.h"

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
CTowerAIState::CTowerAIState()
: m_pTower(0)
{
	
}

/**
*
* Deconstructor for CTowerIdle
*
* @author				Cameron MacIntosh
*
*/
CTowerAIState::~CTowerAIState()
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
CTowerAIState::Initialise(CTower *_pOwnerTower)
{
	if(_pOwnerTower!=0)
	{
		m_pTower = _pOwnerTower;
		return (true);
	}
	return false;
}