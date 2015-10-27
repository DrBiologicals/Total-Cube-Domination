// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   towerdisabled.cpp
//  Description :   towerdisabled.cpp for implementation of towerdisabled.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Includes
#include "towerdisabled.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
*
* Constructor for CTowerDisabled
*
* @author				Cameron MacIntosh
*
*/
CTowerDisabled::CTowerDisabled()
{

}

/**
*
* Deconstructor for CTowerDisabled
*
* @author				Cameron MacIntosh
*
*/
CTowerDisabled::~CTowerDisabled()
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
CTowerDisabled::Initialise(CTower *_pOwnerTower)
{
	if(_pOwnerTower!=0)
	{
		m_pTower = _pOwnerTower;
		m_fDisableTime = 4.0f;	//set disable time to 4 seconds
		return (true);
	}
	return false;
}

/**
*
* Processes the state
*
* @author				Cameron MacIntosh
* @param _fDeltaTick	Time between frames
*
*/
void
CTowerDisabled::Process(float32 _fDeltaTick)
{
	m_fDisableTime -= _fDeltaTick;
	//if the tower is no longer disabled
	if(m_fDisableTime <= 0.0f)
	{
		//set shield strength to full
		m_pTower->SetCurrentShield(m_pTower->GetMaxShield());
		//switch state to idle
		m_pTower->SetAIState(TOWERAI_STATE_IDLE);
	}
}