// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   player.cpp
//  Description :   player.cppfor implementation of player.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "tank.h"
#include "playermanager.h"

// This Includes
#include "player.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer()
: m_iPlayerID(0)
, m_eTeam(TEAM_NEUTRAL)
, m_pTank(0)
, m_bIsHuman(false)
, m_fRespawnTimer(10.0f)
{
}

CPlayer::~CPlayer()
{
}

/*
* 
* @author Michael McQuarrie
* @param _iIDNumber The ID for the tank
* @param _eTeam The team the tank is on
* @param _pTank The pointer to the tank
* @param _tPlayerSpawnlocation the tanks spawn point
* @return bool
*/
bool
CPlayer::Initialise(CTank* _pTank, int32 _iIDNumber, ETeam _eTeam)
{
	//Adding the player number
	m_iPlayerID = _iIDNumber;
	
	//Adding the team 
	m_eTeam = _eTeam;

	//Creating a new tank for the player
	m_pTank = _pTank;

	return (true);
}

/*
* 
* @author Michael McQuarrie
* @author Rebeccah Cox - filled in empty function with respawn functionality that 
*						was in player manager.
* @param _fDeltaTick
* @return void
*/
void
CPlayer::Process(float32 _fDeltaTick)
{
	if(false == m_pTank->GetAlive())
	{
		m_fRespawnTimer -= _fDeltaTick;

		if (m_fRespawnTimer <= 0.0f)
		{
			// reset respawn timer
			m_fRespawnTimer = 10.0f;

			m_pTank->Respawn(CPlayerManager::GetPlayerManagerInstance().GetRandomRespawnLocation(m_pTank, m_eTeam));

			m_pTank->SetAlive(true);
			m_pTank->SetCurrentShield(m_pTank->GetMaxShield());
		}
	}
}

/*
* 
* @author Michael McQuarrie
* @return void
*/
void
CPlayer::Draw()
{
	m_pTank->Draw();
}

/*
* 
* @author Michael McQuarrie
* @return ETeam
*/
ETeam
CPlayer::GetTeam()
{
	return (m_eTeam);
}

/*
* 
* @author Michael McQuarrie
* @return EPlayerNumber
*/
int32 
CPlayer::GetPlayerID()
{
	return (m_iPlayerID);
}

/*
* 
* @author Michael McQuarrie
* @return CTank*
*/
CTank*
CPlayer::GetTank()
{
	return (m_pTank);
}

/*
* Returns if the player instance is a human or otherwise (ie. AIPlayer)
*
* @author	Cameron MacIntosh
* @return	true if a human, false if not
*/
bool
CPlayer::IsHuman() const
{
	return(m_bIsHuman);
}

/*
* Returns the respawn timer
* @author Rigardt de vries
* @return the m_fRespawnTimer.
*/
float32
CPlayer::GetRespawnTimer()
{
    return (m_fRespawnTimer);
}

/*
* SetRespawnTimer
* @author Rigardt de Vries
* @param _fTime         the new time
* @return void
*/
void
CPlayer::SetRespawnTimer(float32 _fTime)
{
    m_fRespawnTimer = _fTime;
}
