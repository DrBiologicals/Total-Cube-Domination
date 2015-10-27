// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   programstate.cpp
//  Description :   CProgramState implementation file.
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../totalcubedomination.h"

// This Includes

#include "programstate.h"

// Static Variables
uint32 CProgramState::s_uiNumPlayers = 0;
bool CProgramState::s_bPlayerIsGreen[4] = {true, true, true, true};
uint32 CProgramState::s_uiLevelID = 0;
uint32 CProgramState::s_uiDifficulty = 0;

// Static Function Prototypes

// Implementation

CProgramState::CProgramState()
: m_pOwner(0)
{
}

CProgramState::~CProgramState()
{
}

/*
* 
* 
* @param CTotalCubeDomination* _pOwner
* @return void 
*/
void
CProgramState::SetOwner(CTotalCubeDomination* _pOwner)
{
	m_pOwner = _pOwner;
}

/**
* 
* Checks if the player associated with the controller ID has chosen 
*	to be on the TEAM_GREEN team (returns true) or the TEAM_PURPLE team (returns false).
* Also only checks if a valid controller ID number has been entered.
* 
* @author Rebeccah Cox
* @param uint32 _uiControllerID
* @return bool 
*/
bool
CProgramState::IsPlayerGreen(uint32 _uiControllerID)
{
	if(_uiControllerID < s_uiNumPlayers)
	{
		return (s_bPlayerIsGreen[_uiControllerID]);
	}
	
	return (false);
}

/**
* 
* Returns the ID number for the level. The ID number is the 
*	position the level is in the list in the LEVEL_SELECT_MENU, starting 
*	at zero.
* 
* @author Rebeccah Cox
* @return uint32 - the level ID number
*/
uint32
CProgramState::GetLevelNumber()
{
	return (s_uiLevelID);
}

/**
* 
* Returns the number of players.
* 
* @author Rebeccah Cox
* @return uint32
*/
uint32
CProgramState::GetNumPlayers()
{
	return (s_uiNumPlayers);
}
uint32
CProgramState::GetDifficulty()
{
	return(s_uiDifficulty);
}
/**
* 
* Sets the player to a team.
* 
* @author Rebeccah Cox
* @param uint32 _uiPlayerID
* @param bool _bIsGreen
* @return void
*/
void
CProgramState::SetPlayerTeam(uint32 _uiPlayerID, bool _bIsGreen)
{
	s_bPlayerIsGreen[_uiPlayerID] = _bIsGreen;
}

/**
* 
* 
* 
* @author Rebeccah Cox
* @param
* @return void
*/
void
CProgramState::SetLevelNumber(uint32 _uiLevelID)
{
	s_uiLevelID = _uiLevelID;
}

/**
* 
*
* 
* @author Rebeccah Cox
* @param
* @return void
*/
void
CProgramState::SetNumPlayer(uint32 _uiNumPlayers)
{
	s_uiNumPlayers = _uiNumPlayers;
}
void
CProgramState::SetDifficulty(uint32 _uiDifficulty)
{
	s_uiDifficulty = _uiDifficulty;
}
